#!/bin/bash
# test-cgi.sh
# by Michael Zick
# Used with permission
# http://tldp.org/LDP/abs/html/networkprogramming.html

# May have to change the location for your site.
# (At the ISP's servers, Bash may not be in the usual place.)
# Other places: /usr/bin or /usr/local/bin
# Might even try it without any path in sha-bang.

# Disable filename globbing.
set -f

# Header tells browser what to expect.
echo Content-type: text/plain
echo

echo CGI/1.0 test script report:
echo

echo environment settings:
set
echo


    echo "--------------------------------------------------------"
#For calculating system work load performance: using bar chart

	#For calculating system work load performance: using bar chart
	declare -i phy_cpu_num=1
	declare -i cpu_core_num=1
	declare -i logical_cpu_num=1

	phy_cpu_num=$(cat /proc/cpuinfo| grep "physical id"| sort| uniq| wc -l)
	echo "phy_cpu_num: "$phy_cpu_num

	cpu_core_num=$(cat /proc/cpuinfo| grep "cpu cores"| uniq)
	echo "cpu_core_num: "$cpu_core_num

	logical_cpu_num=$(cat /proc/cpuinfo| grep "processor"|sort -u |wc -l)
	echo "logical_cpu_num: "$logical_cpu_num

	echo "Threats: "$(cat /proc/cpuinfo | grep "siblings"| sort -n | tail -1 |awk '{print $3}')
	



	# echo "cpu_num: "$cpu_num

	#defining a float point variable to carry the total system performance
	totalWload=$(echo "$logical_cpu_num*1.0" | bc)
	echo "totalWload: "$totalWload

	#/$totalWload
	wload1m=$(echo "scale=2;tmp1=$(uptime | awk '{print $10}'|cut -f 1 -d ",");if(length(tmp1)==scale(tmp1)) print 0;print tmp1" | bc)
	echo "wload1m: "$wload1m
	wload5m=$(echo "scale=2;tmp2=$(uptime | awk '{print $11}'|cut -f 1 -d ",");if(length(tmp2)==scale(tmp2)) print 0;print tmp2"| bc)
	echo "wload5m: "$wload5m
	wload15m=$(echo "scale=2;tmp3=$(uptime | awk '{print $NF}'|cut -f 1 -d ",");if(length(tmp3)==scale(tmp3)) print 0;print tmp3"| bc)
	echo "wload15m: "$wload15m

	#For calculating system CPU performance: using pie chart
	CPUload_us=$(echo "tmp=$(top -b -n 1 | grep Cpu | awk '{print $2}');if(length(tmp)==scale(tmp)) print 0;print tmp" |bc)
	echo "CPUload_us: "$CPUload_us

	CPUload_sy=$(echo "tmp=$(top -b -n 1 | grep Cpu | awk '{print $4}');if(length(tmp)==scale(tmp)) print 0;print tmp" |bc)
	echo "CPUload_sy: "$CPUload_sy

	CPUload_ni=$(echo "tmp=$(top -b -n 1 | grep Cpu | awk '{print $6}');if(length(tmp)==scale(tmp)) print 0;print tmp" |bc)
	echo "CPUload_ni: "$CPUload_ni

	CPUload_id=$(echo "tmp=$(top -b -n 1 | grep Cpu | awk '{print $8}');if(length(tmp)==scale(tmp)) print 0;print tmp" |bc)
	echo "CPUload_id: "$CPUload_id

	CPUload_wa=$(echo "tmp=$(top -b -n 1 | grep Cpu | awk '{print $10}');if(length(tmp)==scale(tmp)) print 0;print tmp" |bc)
	echo "CPUload_wa: "$CPUload_wa


	#For calculating system memory usuage: using pie chart
	let MEM_total=$(free -m | grep Mem | awk '{print $2}')
	echo "MEM_total: "$MEM_total
	let MEM_phy_F=$(free -m | grep Mem | awk '{print $4}')
	echo "MEM_phy_F: "$MEM_phy_F
	let MEM_cach_F=$(free -m | grep - | awk '{print $NF}')-$MEM_phy_F
	echo "MEM_cach_F: "$MEM_cach_F
	let MEM_used=$(free -m | grep - | awk '{print $3}')
	echo "MEM_used: "$MEM_used

	#free -m | grep - | awk '{print $4}'
	#swap_total=`free -m | grep Swap | awk '{print  $2}'`  
	#swap_free=`free -m | grep Swap | awk '{print  $4}'`
	#swap_used=`free -m | grep Swap | awk '{print  $3}'`


	#For calculating system disk usuage: using pie chart
	#df -k | grep -v Filesystem| awk '{print int($5)}'
	let DISK_us=$(df -h | awk '{print $5}' | grep % | grep -v Use | sort -n | tail -1 | cut -d "%" -f1 -)
	echo "DISK_us: "$DISK_us
	let DISK_fr=100-$DISK_us
	echo "DISK_fr: "$DISK_fr

  echo "--------------------------------------------------------"




echo whereis bash?
whereis bash
echo


echo who are we?
echo ${BASH_VERSINFO[*]}
echo

echo argc is $#. argv is "$*".
echo

# CGI/1.0 expected environment variables.

echo SERVER_SOFTWARE = $SERVER_SOFTWARE
echo SERVER_NAME = $SERVER_NAME
echo GATEWAY_INTERFACE = $GATEWAY_INTERFACE
echo SERVER_PROTOCOL = $SERVER_PROTOCOL
echo SERVER_PORT = $SERVER_PORT
echo REQUEST_METHOD = $REQUEST_METHOD
echo HTTP_ACCEPT = "$HTTP_ACCEPT"
echo PATH_INFO = "$PATH_INFO"
echo PATH_TRANSLATED = "$PATH_TRANSLATED"
echo SCRIPT_NAME = "$SCRIPT_NAME"
echo QUERY_STRING = "$QUERY_STRING"
echo REMOTE_HOST = $REMOTE_HOST
echo REMOTE_ADDR = $REMOTE_ADDR
echo REMOTE_USER = $REMOTE_USER
echo AUTH_TYPE = $AUTH_TYPE
echo CONTENT_TYPE = $CONTENT_TYPE
echo CONTENT_LENGTH = $CONTENT_LENGTH

exit 0