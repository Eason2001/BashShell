#!/bin/bash
# Dr. Ziad Kobti (c)2017
# Lab 3c - sample sum

# load the library functions
source ./lab3lib.cgi

if [ "x$alertvalue" != "x" ]; then
	
	#For calculating system work load performance:
	declare -i cpu_num=`grep -c 'model name' /proc/cpuinfo`
	declare -i wload1m=$((uptime | awk '{print $8}')/cpu_num)
	declare -i wload5m=$((uptime | awk '{print $9}')/cpu_num)
	declare -i wload15m=$((uptime | awk '{print $NF}')/cpu_num)

	#For calculating system CPU performance:
	declare -i CPUload_us=$(top -b -n 1 | grep Cpu | awk '{print $2}' | cut -f 1 -d ".")
	declare -i CPUload_sy=$(top -b -n 1 | grep Cpu | awk '{print $4}' | cut -f 1 -d ".")
	declare -i CPUload_ni=$(top -b -n 1 | grep Cpu | awk '{print $6}' | cut -f 1 -d ".")
	declare -i CPUload_id=$(top -b -n 1 | grep Cpu | awk '{print $8}' | cut -f 1 -d ".")
	declare -i CPUload_wa=$(top -b -n 1 | grep Cpu | awk '{print $10}' | cut -f 1 -d ".")



  # This script does a very simple test for checking disk space.
	space=`df -h | awk '{print $5}' | grep % | grep -v Use | sort -n | tail -1 | cut -d "%" -f1 -`
	let gap=" 100 - $space "
	if [ "$space" -ge "$alertvalue" ]; then
	message2="At least one of my disks is nearly full!"
	else
	message2="Disk space normal at ${space}%"
	fi

	cat <<EOFA
	<html>
	<body>
	${message2}
	<img src="./images/1by1red.gif" height="20" width="${space}">
	<img src="./images/1by1green.gif" height="20" width="${gap}">
	</body>
	</html>
	EOFA


else

	cat <<EOFB
	<html>
	<body>
	Enter the alert value for the disk space:<br/><br/>
	<form action="?version=${version:=1}" method="POST" enctype="application/x-www-form-urlencoded">
	Alert value: <input type="text" name="alertvalue" value="$alertvalue"><br/><br/>
	<input type="submit">
	</form>
	</body>
	</html>
	EOFB

fi
