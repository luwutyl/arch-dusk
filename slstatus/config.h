/* See LICENSE file for copyright and license details. */

/* interval between updates (in ms) */
const unsigned int interval = 1000;

/* text to show if no value can be retrieved */
static const char unknown_str[] = "n/a";

/* maximum output string length */
#define MAXLEN 2048

/*
 * function            description                     argument (example)
 *
 * battery_perc        battery percentage              battery name (BAT0)
 *                                                     NULL on OpenBSD/FreeBSD
 * battery_state       battery charging state          battery name (BAT0)
 *                                                     NULL on OpenBSD/FreeBSD
 * battery_remaining   battery remaining HH:MM         battery name (BAT0)
 *                                                     NULL on OpenBSD/FreeBSD
 * cpu_perc            cpu usage in percent            NULL
 * cpu_freq            cpu frequency in MHz            NULL
 * datetime            date and time                   format string (%F %T)
 * disk_free           free disk space in GB           mountpoint path (/)
 * disk_perc           disk usage in percent           mountpoint path (/)
 * disk_total          total disk space in GB          mountpoint path (/")
 * disk_used           used disk space in GB           mountpoint path (/)
 * entropy             available entropy               NULL
 * gid                 GID of current user             NULL
 * hostname            hostname                        NULL
 * ipv4                IPv4 address                    interface name (eth0)
 * ipv6                IPv6 address                    interface name (eth0)
 * kernel_release      `uname -r`                      NULL
 * keyboard_indicators caps/num lock indicators        format string (c?n?)
 *                                                     see keyboard_indicators.c
 * keymap              layout (variant) of current     NULL
 *                     keymap
 * load_avg            load average                    NULL
 * netspeed_rx         receive network speed           interface name (wlan0)
 * netspeed_tx         transfer network speed          interface name (wlan0)
 * num_files           number of files in a directory  path
 *                                                     (/home/foo/Inbox/cur)
 * ram_free            free memory in GB               NULL
 * ram_perc            memory usage in percent         NULL
 * ram_total           total memory size in GB         NULL
 * ram_used            used memory in GB               NULL
 * run_command         custom shell command            command (echo foo)
 * swap_free           free swap in GB                 NULL
 * swap_perc           swap usage in percent           NULL
 * swap_total          total swap size in GB           NULL
 * swap_used           used swap in GB                 NULL
 * temp                temperature in degree celsius   sensor file
 *                                                     (/sys/class/thermal/...)
 *                                                     NULL on OpenBSD
 *                                                     thermal zone on FreeBSD
 *                                                     (tz0, tz1, etc.)
 * uid                 UID of current user             NULL
 * uptime              system uptime                   NULL
 * username            username of current user        NULL
 * vol_perc            OSS/ALSA volume in percent      mixer file (/dev/mixer)
 * wifi_perc           WiFi signal in percent          interface name (wlan0)
 * wifi_essid          WiFi ESSID                      interface name (wlan0)
 */

static const char vol[] = "muted=`wpctl get-volume @DEFAULT_SINK@ | awk '{print $3;}'`; \
                            volume=`wpctl get-volume @DEFAULT_SINK@ | awk '{print $2;}'`; \
                            if [ -z ${muted} ]; then \
                                printf \"${volume}\"; \
                            else printf \"MUTED\"; \
                            fi";

static const char mic[] = "muted=`wpctl get-volume @DEFAULT_SOURCE@ | awk '{print $3;}'`; \
                            volume=`wpctl get-volume @DEFAULT_SOURCE@ | awk '{print $2;}'`; \
                            if [ -z ${muted} ]; then \
                                printf \"${volume}\"; \
                            else printf \"MUTED\"; \
                            fi";

//  static const struct arg args[] = {
//      /* function format          argument */
//	 { ipv4,          "| 󰈀 %s ",      "enp4s0" },
//	 { wifi_perc,     "|   %s%% ",  "wlan0" },
//     { netspeed_rx,   "^c#B0E0E6^^b#B0E0E6^ ^c#000000^ %s/s ",        "enp4s0" },
//     { netspeed_tx,   " %s/s ",          "enp4s0" },
//     { keymap,        "^c#87CEEB^^b#87CEEB^ ^c#000000^󰌌 %s ",     NULL },
//     { run_command,   "^c#00bfff^^b#00bfff^ ^c#000000^ %s ",       "sensors k10temp-pci-00c3 | grep 'Tccd1:' | awk '{print $2}' | tr -d '+'" },
//     { run_command,   "^c#1E90FF^^b#1E90FF^ ^c#000000^󰢮 %s ",       "sensors amdgpu-pci-0500 | grep 'edge:' | awk '{print $2}' | tr -d '+'" },
//  	 { cpu_perc,      "^c#00CED1^^b#00CED1^ ^c#000000^ %s%% ",   NULL },
//     { run_command,   "^c#7FFFD4^^b#7FFFD4^ ^c#000000^ %s",        "free -h | grep 'Mem:' | awk '{print $3}'" },
//	 { ram_perc,      "|  %s%% ",   NULL },
//	 { battery_perc,  "|  %s%%",    "BAT0" },
//	 { battery_state, "(%s) ",       "BAT0" },
//	 { run_command,   "| 󰃝 %s%% ",   "xbacklight -get" },
//	 { run_command,   "|   %s ",    vol },
//	 { run_command,   "|  %s ",     mic },
//  	 { datetime,      "^c#40E0D0^^b#40E0D0^ ^c#000000^ %s ",     "%a %F %T" }, /* Date time with this format: YYYY-MM-DD 18:00:00 */
//};

static const struct arg args[] = {
    /* function        format                                           argument */

    /* RX / TX — почти чёрный фиолет */
    { netspeed_rx, "^c#5E3A8C^^b#5E3A8C^ ^c#000000^ %s/s ", "enp4s0" },
    { netspeed_tx, " %s/s ",                                 "enp4s0" },

    /* Keymap — тёмный violet */
    { keymap, "^c#6F44A6^^b#6F44A6^ ^c#000000^󰌌 %s ", NULL },

    /* CPU temp — насыщенный фиолет */
    { run_command,
      "^c#864FCE^^b#864FCE^ ^c#000000^ %s ",
      "sensors k10temp-pci-00c3 | grep 'Tccd1:' | awk '{print $2}' | tr -d '+'" },

    /* GPU temp — ближе к плазме */
    { run_command,
      "^c#9A4FFF^^b#9A4FFF^ ^c#000000^󰢮 %s ",
      "sensors amdgpu-pci-0500 | grep 'edge:' | awk '{print $2}' | tr -d '+'" },

    /* CPU usage — яркий violet */
    { cpu_perc, "^c#B94CFF^^b#B94CFF^ ^c#000000^ %s%% ", NULL },

    /* RAM — plasma magenta */
    { run_command,
      "^c#D94CFF^^b#D94CFF^ ^c#000000^ %s",
      "free -h | grep 'Mem:' | awk '{print $3}'" },

    /* Date / time — пик энергии */
    { datetime,
      "^c#FF4CFF^^b#FF4CFF^ ^c#000000^ %s ^c#FF4CFF^^b#0B0014^",
      "%a %F %T" },
};
