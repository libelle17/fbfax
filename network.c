/**
 * The libroutermanager project
 * Copyright (c) 2012-2014 Jan-Michael Brummer
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */
#include <libsoup/soup.h>
#include <string.h>
#include "gstring.h"
#include "network.h"
#include "appobject-emit.h"
#undef g_debug
#define g_debug(format...)    g_log_structured (G_LOG_DOMAIN, G_LOG_LEVEL_DEBUG,     \
                                                "CODE_FILE", __FILE__,               \
                                                "CODE_LINE", G_STRINGIFY (__LINE__), \
                                                "CODE_FUNC", G_STRFUNC,               \
                                                "MESSAGE", format)
/** Soup session */
SoupSession *soup_session = NULL;

static void free_auth_data(struct auth_data *auth_data)
{
        g_object_unref(auth_data->msg);
        g_free(auth_data->username);
        g_free(auth_data->password);
        g_slice_free(struct auth_data, auth_data);
}

/* libsoup 3: msg->status_code -> soup_message_get_status(msg) */
static void save_password_callback(SoupMessage *msg, struct auth_data *auth_data)
{
        guint status_code = soup_message_get_status(msg);
        if (status_code != 401 && status_code < 500) {
                // Kommentar 4.1.18
                /*
                struct profile *profile = profile_get_active();
                */
/*
                usr=auth_data->username;
                pwd=auth_data->password;
                */
                g_debug("%s(): Storing data for later processing", __FUNCTION__);
        }
        g_signal_handlers_disconnect_by_func(msg, (gpointer)save_password_callback, auth_data);
        free_auth_data(auth_data);
}

void network_authenticate(gboolean auth_set, struct auth_data *auth_data)
{
        g_debug("%s(): calling authenticate", __FUNCTION__);
        if (auth_set) {
                soup_auth_authenticate(auth_data->auth, auth_data->username, auth_data->password);
                g_signal_connect(auth_data->msg, "got-headers", G_CALLBACK(save_password_callback), auth_data);
        }
        /* libsoup 3: soup_session_pause/unpause_message entfernt.
         * Authentifizierung laeuft jetzt synchron im authenticate-Signal.
         * Kein Pausieren noetig – soup_auth_authenticate() genuegt. */
        if (!auth_set) {
                free_auth_data(auth_data);
        }
}

/* libsoup 3: authenticate-Signal hat neue Signatur:
 * gboolean network_authenticate_cb(SoupMessage*, SoupAuth*, gboolean, gpointer)
 * session-Parameter entfernt */
static gboolean network_authenticate_cb(SoupMessage *msg, SoupAuth *auth, gboolean retrying, gpointer user_data)
{
        struct auth_data *auth_data;
        const gchar *user{0};
        const gchar *password{0};
        guint status_code = soup_message_get_status(msg);

        g_debug("%s(): retrying: %d, status code: %d == %d", __FUNCTION__, retrying, status_code, SOUP_STATUS_UNAUTHORIZED);

        if (status_code != SOUP_STATUS_UNAUTHORIZED) {
                return FALSE;
        }

        /* libsoup 3: kein pause/unpause mehr noetig */
        g_object_ref(msg);

        if (!retrying && !EMPTY_STRING(user) && !EMPTY_STRING(password)) {
                g_debug("%s(): Already configured...", __FUNCTION__);
                soup_auth_authenticate(auth, user, password);
                g_object_unref(msg);
                return TRUE;
        } else {
                auth_data = g_slice_new0(struct auth_data);
                auth_data->msg = msg;
                auth_data->auth = auth;
                auth_data->session = (SoupSession *)user_data;
                auth_data->retry = retrying;
                auth_data->username = g_strdup(user);
                auth_data->password = g_strdup(password);
                emit_authenticate(auth_data);
                return TRUE;
        }
}

/**
 * \brief Initialize network functions
 * \return TRUE on success, otherwise FALSE
 */
gboolean net_init(void)
{
        /* libsoup 3: SOUP_SESSION_TIMEOUT entfernt,
         * stattdessen soup_session_set_timeout() verwenden */
        soup_session = soup_session_new();
        soup_session_set_timeout(soup_session, 5);
        /* libsoup 3: SoupSession::authenticate wurde entfernt.
         * Das Signal wird jetzt pro SoupMessage verbunden –
         * siehe network_new_message(). */
        return soup_session != NULL;
}

/**
 * \brief Create a new SoupMessage and connect the libsoup-3 per-message
 *        authenticate signal to it.
 * \param method      HTTP method string, e.g. SOUP_METHOD_GET
 * \param uri_string  target URL
 * \return new SoupMessage, or NULL on error
 */
SoupMessage *network_new_message(const gchar *method, const gchar *uri_string)
{
        SoupMessage *msg = soup_message_new(method, uri_string);
        if (msg) {
                g_signal_connect(msg, "authenticate",
                                 G_CALLBACK(network_authenticate_cb), soup_session);
        }
        return msg;
}

/**
 * \brief Deinitialize network infrastructure
 */
void net_shutdown(void)
{
        g_clear_object(&soup_session);
}
