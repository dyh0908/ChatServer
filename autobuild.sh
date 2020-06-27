##########################################
# File name : autobuild.sh
# Author : Deng Yaohui
# Mail : 272692851@qq.com
# Created Time : 2020年6月27号 星期六 19时19分19秒
##########################################
#!bin/bash


set -x

rm -rf `pwd`/build/*
cd `pwd`/build &&
	cmake .. &&
	make
