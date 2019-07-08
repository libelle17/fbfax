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

/**
 * TODO:
 *  - get rid of active_capi_connection?
 *  - merge connection-XXXX signals
 */

#include <gio/gio.h>
#include <string.h>
#include <stdlib.h>

#include "appobject-emit.h"
#include "net_monitor.h"
#include "profile.h"
// #include "router.h"
#include "audio.h"
// #include "call.h"
// #include "gstring.h"

#include "faxophone.h"
#include "fax.h"
// #include "sff.h"
#include "phone.h"
// #include "ringtone.h"
#undef g_debug
#define g_debug(format...)    g_log_structured (G_LOG_DOMAIN, G_LOG_LEVEL_DEBUG,     \
                                                "CODE_FILE", __FILE__,               \
                                                "CODE_LINE", G_STRINGIFY (__LINE__), \
                                                "CODE_FUNC", G_STRFUNC,               \
                                                "MESSAGE", format)


#define RM_ERROR 

//extern int verbg;
extern GMainContext *ctx;
// aus gmain.c , g_idle_add_full
guint 
g_idle_add_full_con (gint           priority,
		 GSourceFunc    function,
		 gpointer       data,
		 GDestroyNotify notify,
		 GMainContext *context)
{
  GSource *source;
  guint id;
  
  g_return_val_if_fail (function != NULL, 0);

  source = g_idle_source_new ();

  if (priority != G_PRIORITY_DEFAULT_IDLE)
    g_source_set_priority (source, priority);

  g_source_set_callback (source, function, data, notify);
  id = g_source_attach (source, context);

  // TRACE (GLIB_IDLE_ADD (source, g_main_context_default (), id, priority, function, data));

  g_source_unref (source);

  return id;
}

// aus gmain.c , g_idle_add
guint
g_idle_add_con (GSourceFunc    function,
	    gpointer       data,
			GMainContext *context)
{
  return g_idle_add_full_con (G_PRIORITY_DEFAULT_IDLE, function, data, NULL,context);
}

///*static */struct session *session = NULL;
// static gconstpointer net_event;

struct capi_connection *active_capi_connection = NULL;
/**
 * \brief Connection ring handler
 * \param connection capi connection structure
 */
gboolean connection_ring_idle(gpointer data)
{
	struct capi_connection *capi_connection = (struct capi_connection*)data;
	struct connection *connection;

	active_capi_connection = capi_connection;

	g_debug("connection_ring() src %s trg %s", capi_connection->source, capi_connection->target);
	connection = connection_find_by_number(capi_connection->source);
#if ACCEPT_INTERN
	if (!connection && !strncmp(capi_connection->source, "**", 2)) {
		connection = connection_add_call(981, CONNECTION_TYPE_INCOMING, capi_connection->source, capi_connection->target);
	}
#endif

	g_debug("connection_ring() connection %p", connection);
	if (connection) {
		g_debug("connection_ring() set capi_connection %p", capi_connection);
		connection->priv = capi_connection;

		emit_connection_notify(connection);
	}

	return G_SOURCE_REMOVE;
}

void connection_ring(struct capi_connection *capi_connection)
{
	if (ctx) g_idle_add_con(connection_ring_idle, capi_connection,ctx);
	else g_idle_add(connection_ring_idle, capi_connection);
}


/**
 * \brief Connection code handler
 * \param connection capi connection structure
 * \param code dtmf code
 */
void connection_code(struct capi_connection *connection, gint code)
{
	g_debug("connection_code(): code 0x%x", code);
}

/**
 * \brief Connection status handlers - emits connection-status signal
 * \param connection capi connection structure
 * \param status status code
 */
void connection_status(struct capi_connection *connection, gint status)
{
//	if (verbg) printf("Beginn connection_status\n");
	emit_connection_status(status, connection);
//	if (verbg) printf("Ende connection_status\n");
}

gboolean connection_established_idle(gpointer data)
{
	struct capi_connection *connection = (struct capi_connection*)data;

	emit_connection_established(connection);

	return G_SOURCE_REMOVE;
}

void connection_established(struct capi_connection *connection)
{
	if (ctx) g_idle_add_con(connection_established_idle, connection,ctx);
	else g_idle_add(connection_established_idle, connection);
}

gboolean connection_terminated_idle(gpointer data)
{
	struct capi_connection *connection = (struct capi_connection*)data;
	emit_connection_terminated(connection);
	return G_SOURCE_REMOVE;
}

void connection_terminated(struct capi_connection *connection)
{
	if (ctx) g_idle_add_con(connection_terminated_idle, connection,ctx);
	else g_idle_add(connection_terminated_idle, connection);
}

struct session_handlers_st session_handlers = {
	audio_open, /* audio_open */
	audio_read, /* audio_read */
	audio_write, /* audio_write */
	audio_close, /* audio_close */

	connection_established, /* connection_established */
	connection_terminated, /* connection_terminated */
	connection_ring, /* connection_ring */
	connection_code, /* connection_code */
	connection_status, /* connection_status */
};


/**
 * \brief Network disconnect callback
 * \param user_data faxophone plugin pointer
 * \return TRUE
 */
// gboolean faxophone_disconnect(gpointer user_data)
// {
// 	if (verbg) printf("Beginn faxophone_disconnect\n");
// 	faxophone_close(TRUE);
// 	return TRUE;
// }

/**
 * \brief Init faxophone support
 */
// void faxophone_setup(void)
// {
// 	if (verbg) printf("Beginn faxophone_setup\n");
// 	net_event = net_add_event(faxophone_connect, faxophone_disconnect, NULL);
// }
