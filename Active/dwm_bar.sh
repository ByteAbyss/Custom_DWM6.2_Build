#!/bin/bash

dte(){
  dte="$(date +"%B %d | %l:%M %p")"
  echo -e "$dte"
}

mem(){
  mem=`free | awk '/Mem/ {printf "%d/%d MB\n", $3 / 1024.0, $2 / 1024.0 }'`
  echo -e "$mem"
}

cpu(){
  read cpu a b c previdle rest < /proc/stat
  prevtotal=$((a+b+c+previdle))
  sleep 0.5
  read cpu a b c idle rest < /proc/stat
  total=$((a+b+c+idle))
  cpu=$((100*( (total-prevtotal) - (idle-previdle) ) / (total-prevtotal) ))
  echo -e "$cpu%"
}


print_wifi() {
	ip=$(ip route get 8.8.8.8 2>/dev/null|grep -Eo 'src [0-9.]+'|grep -Eo '[0-9.]+')

	if=wlan0
		while IFS=$': \t' read -r label value
		do
			case $label in SSID) SSID=$value
				;;
			signal) SIGNAL=$value
				;;
		esac
	done < <(iw "$if" link)

	echo -e "IP: $SSID $SIGNAL $ip"
}



print_temp(){
	test -f /sys/class/thermal/thermal_zone0/temp || return 0
	echo $(head -c 2 /sys/class/thermal/thermal_zone0/temp)C
}


weather(){
#!/bin/sh
### This is only if your location isn't automatically detected, otherwise you can leave it blank.
location="03857"

[ "$location" != "" ] && location="$location+"

[ "$BLOCK_BUTTON" = "1" ] && $TERMINAL -e popweather

ping -q -w 1 -c 1 "$(ip r | grep default | tail -1 | cut -d ' ' -f 3)" >/dev/null || exit

curl -s wttr.in/$location > ~/.weatherreport 

printf "%s" "$(sed '16q;d' ~/.weatherreport | grep -wo "[0-9]*%" | sort -n | sed -e '$!d' | sed -e "s/^/  /g" | tr -d '\n')"

sed '13q;d' ~/.weatherreport | grep -o "m\\(-\\)*[0-9]\\+" | sort -n -t 'm' -k 2n | sed -e 1b -e '$!d' | tr '\n|m' ' ' | awk '{print " Low:",$1 "°","High:",$2 "°"}'

}


#   amixer get Master | head -6 | grep -o "[0-9]*%\|\[on\]\|\[off\]"|sed "s/\[on\]//;s/\[off\]//"
volume() { 
amixer sget Master | grep -e 'Front Left:' | \
    sed 's/[^\[]*\[\([0-9]\{1,3\}%\).*\(on\|off\).*/\2 \1/' | sed 's/off/Muted/' | sed 's/on //'
}


while true; do
	xsetroot -name " $(weather) |   $(cpu) |  $(mem) |  墳 $(volume) | 﨏 $(print_temp) | $(dte) " 
     sleep 5s    # Update time every five  seconds
done &





