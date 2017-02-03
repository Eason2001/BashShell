#!/bin/bash
# Dr. Ziad Kobti (c)2017
# Lab 3a - sample sum

# load the library functions
source ./lab3lib.cgi

let "sum = $num1 + $num2"

cat <<EOF
	<html>
	<body>
	Enter two numbers to compute their sum:<br/><br/>
	<form action="?version=${version:=1}" method="POST" enctype="application/x-www-form-urlencoded">
	num1: <input type="text" name="num1" value="$num1"><br/>
	num2: <input type="text" name="num2" value="$num2"><br/><br/>
	sum: <input type="text" name="sum" value="$sum"><br/><br/>
	<input type="submit">
	</form>
	</body>
	</html>
EOF

