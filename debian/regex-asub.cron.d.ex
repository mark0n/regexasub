#
# Regular cron jobs for the regex-asub package
#
0 4	* * *	root	[ -x /usr/bin/regex-asub_maintenance ] && /usr/bin/regex-asub_maintenance
