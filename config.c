#include <getopt.h>

#include "mediator.h"
#include "config.h"

unsigned int config_interval = MEDIATOR_DEFAULT_INTERVAL;
u_int8_t config_dumpcdr = MEDIATOR_DEFAULT_DUMPCDR;
u_int8_t config_daemonize = MEDIATOR_DEFAULT_DAEMONIZE;
char *config_pid_path = MEDIATOR_DEFAULT_PIDPATH;

char *config_med_host = MEDIATOR_DEFAULT_ACCHOST;
char *config_med_user = MEDIATOR_DEFAULT_ACCUSER;
char *config_med_pass = MEDIATOR_DEFAULT_ACCPASS;
char *config_med_db = MEDIATOR_DEFAULT_ACCDB;
unsigned int config_med_port = MEDIATOR_DEFAULT_ACCPORT;

char *config_cdr_host = MEDIATOR_DEFAULT_CDRHOST;
char *config_cdr_user = MEDIATOR_DEFAULT_CDRUSER;
char *config_cdr_pass = MEDIATOR_DEFAULT_CDRPASS;
char *config_cdr_db = MEDIATOR_DEFAULT_CDRDB;
unsigned int config_cdr_port = MEDIATOR_DEFAULT_CDRPORT;

char *config_prov_host = MEDIATOR_DEFAULT_PROVHOST;
char *config_prov_user = MEDIATOR_DEFAULT_PROVUSER;
char *config_prov_pass = MEDIATOR_DEFAULT_PROVPASS;
char *config_prov_db = MEDIATOR_DEFAULT_PROVDB;
unsigned int config_prov_port = MEDIATOR_DEFAULT_PROVPORT;

static u_int8_t config_pid_path_free = 0;

static u_int8_t config_med_host_free = 0;
static u_int8_t config_med_user_free = 0;
static u_int8_t config_med_pass_free = 0;
static u_int8_t config_med_db_free = 0;

static u_int8_t config_cdr_host_free = 0;
static u_int8_t config_cdr_user_free = 0;
static u_int8_t config_cdr_pass_free = 0;
static u_int8_t config_cdr_db_free = 0;


static void config_help(const char *self)
{
	printf("mediator 1.2.0 - Creates call detail records from OpenSER accounting.\n" \
		"Usage: %s [-?] [-d] [-D pidpath]\n" \
		"  -D\tThe path of the PID file (default = '%s').\n" \
		"  -d\tEnables daemonization of the process (default = disabled).\n" \
		"  -l\tEnables dumping of CDRs to syslog (default = disabled).\n" \
		"  -i\tThe creation interval (default = %d).\n" \
		"  -h\tThe ACC db host (default = '%s').\n" \
		"  -o\tThe ACC db port (default = '%d').\n" \
		"  -u\tThe ACC db user (default = '%s').\n" \
		"  -p\tThe ACC db pass (default = '%s').\n" \
		"  -b\tThe ACC db name (default = '%s').\n" \
		"  -H\tThe CDR db host (default = '%s').\n" \
		"  -O\tThe CDR db port (default = '%d').\n" \
		"  -U\tThe CDR db user (default = '%s').\n" \
		"  -P\tThe CDR db pass (default = '%s').\n" \
		"  -B\tThe CDR db name (default = '%s').\n" \
		"  -S\tThe prov db host (default = '%s').\n" \
		"  -T\tThe prov db port (default = '%d').\n" \
		"  -R\tThe prov db user (default = '%s').\n" \
		"  -A\tThe prov db pass (default = '%s').\n" \
		"  -N\tThe prov db name (default = '%s').\n" \
		"  -?\tDisplays this message.\n",
		self, config_pid_path, config_interval,
		config_med_host, config_med_port, config_med_user, config_med_pass, config_med_db,
		config_cdr_host, config_cdr_port, config_cdr_user, config_cdr_pass, config_cdr_db,
		config_prov_host, config_prov_port, config_prov_user, config_prov_pass, config_prov_db);
}

int config_parse_cmdopts(int argc, char **argv)
{
	int c;

	while((c = getopt(argc, argv, "D:i:dl?h:u:p:b:o:H:U:P:B:O:")) != -1)
	{
		if(c == '?')
		{
			config_help(argv[0]);
			exit(0);
		}
		else if(c == 'd')
		{
			config_daemonize = 1;
		}
		else if(c == 'l')
		{
			config_dumpcdr = 1;
		}
		else if(c == 'D')
		{
			config_pid_path = (char*)strdup(optarg);
			config_pid_path_free = 1;
		}
		else if(c == 'i')
		{
			config_interval = atoi(optarg);
		}
		else if(c == 'h')
		{
			config_med_host = (char*)strdup(optarg);
			config_med_host_free = 1;
		}
		else if(c == 'u')
		{
			config_med_user = (char*)strdup(optarg);
			config_med_user_free = 1;
		}
		else if(c == 'p')
		{
			config_med_pass = (char*)strdup(optarg);
			config_med_pass_free = 1;
		}
		else if(c == 'b')
		{
			config_med_db = (char*)strdup(optarg);
			config_med_db_free = 1;
		}
		else if(c == 'o')
		{
			config_med_port = atoi(optarg);
		}
		else if(c == 'H')
		{
			config_cdr_host = (char*)strdup(optarg);
			config_cdr_host_free = 1;
		}
		else if(c == 'U')
		{
			config_cdr_user = (char*)strdup(optarg);
			config_cdr_user_free = 1;
		}
		else if(c == 'P')
		{
			config_cdr_pass = (char*)strdup(optarg);
			config_cdr_pass_free = 1;
		}
		else if(c == 'B')
		{
			config_cdr_db = (char*)strdup(optarg);
			config_cdr_db_free = 1;
		}
		else if(c == 'O')
		{
			config_cdr_port = atoi(optarg);
		}
	}

	return 0;
}

void config_cleanup()
{
	if(config_pid_path_free)
	{
		free(config_pid_path);
	}
	if(config_cdr_host_free)
	{
		free(config_cdr_host);
	}
	if(config_cdr_user_free)
	{
		free(config_cdr_user);
	}
	if(config_cdr_pass_free)
	{
		free(config_cdr_pass);
	}
	if(config_cdr_db_free)
	{
		free(config_cdr_db);
	}
	if(config_med_host_free)
	{
		free(config_med_host);
	}
	if(config_med_user_free)
	{
		free(config_med_user);
	}
	if(config_med_pass_free)
	{
		free(config_med_pass);
	}
	if(config_med_db_free)
	{
		free(config_med_db);
	}
}
