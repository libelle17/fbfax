test $(hostname) = linux1.site && ziel=6150166 || ziel=616381;
make debug install && G_MESSAGES_DEBUG=all gdb -ex "b appobject.c:233" -ex "b appobject.c:228" -ex "b appobject.c:83" -ex "b gemessages.c:1341" -ex "catch signal SIGSEGV" --args fbfax -v -dt /DATA/down/billing_19034615_4373c02ac8fc2.pdf -an $ziel;
