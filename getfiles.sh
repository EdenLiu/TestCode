#!/bin/sh

cd /usr/local/bin
ls >> /data/exe.txt
echo "------------------" >> /data/exe.txt
cd /usr/bin
ls >> /data/exe.txt
echo "------------------" >> /data/exe.txt
cd /bin
ls >> /data/exe.txt
echo "------------------" >> /data/exe.txt
cd /sbin
ls >> /data/exe.txt
echo "------------------" >> /data/exe.txt