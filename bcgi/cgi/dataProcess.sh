#!/bin/bash
#Lab 3c - system performance data process

	#For calculating system work load performance: using bar chart
	declare -i cpu_num=1
	cpu_num=`grep -c 'model name' /proc/cpuinfo`
	echo "cpu_num: "$cpu_num

	#defining a float point variable to carry the total system performance
	totalWload=$(echo "$cpu_num*1.0" | bc)
	echo "totalWload: "$totalWload

	wload1m=$(echo "scale=2;tmp=$(uptime | awk '{print $10}'|cut -f 1 -d ",")/$totalWload;if(length(tmp)==scale(tmp)) print 0;print tmp" | bc)
	echo "wload1m: "$wload1m
	wload5m=$(echo "scale=2;tmp=$(uptime | awk '{print $11}'|cut -f 1 -d ",")/$totalWload;if(length(tmp)==scale(tmp)) print 0;print tmp"| bc)
	echo "wload5m: "$wload5m
	wload15m=$(echo "scale=2;tmp=$(uptime | awk '{print $NF}'|cut -f 1 -d ",")/$totalWload;if(length(tmp)==scale(tmp)) print 0;print tmp"| bc)
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
	let MEM_cach_F=$(free -m | grep - | awk '{print $NF}')
	echo "MEM_cach_F: "$MEM_cach_F
	let MEM_used=$MEM_total-$MEM_phy_F-$MEM_cach_F
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







