#partition
1. Master Boot Record (446 bytes)
2. partition table (64bytes)
    Because the partition table has only 64bytes, it can at most devide the disk into 4 partitions, which we call "primary" or "extended" partitions. We can have at most 4(primary+extended)partions, at most 1 extended partition. The logical partition(s) are derived from the extended partition.
#MBR&&loader
1. If someone wants to install both windows and linux OS on his computer, he is recommended to first install windows and then linux. Beacause when installing linux, you can manually chose where to install the linux-boot-loader, in MBR partition or other partitions. While the windows installing program will automatically cover the previous MBR partition, thus the previous installed linux OS is unable to be loaded.
#directory tree
1. root directory /
    | /boot | /dev | /etc | /bin | /home | /usr | /var | ...
#file property

1.  ls -al 
   total 2000

drwxr-xr-x 1 connection(s) fileowner fileownerGroup size lastModifiedTime filename

"drwxr-xr-x" : file type|file owner's authority|file owner group's authority|other's authority 



\[d\]: directory

\[-\]: file

\[l\]: linkfile

\[b\]: block device file

\[c\]: character device file

\[r\]: read

\[w\]: write

\[x\]: execute

\[-\]: no authority

2. ​
```Shell
chgrp \[-R\] dirname\\filename
#change file's user group
chown 
#change file's owner
chmod \[u=rwx\] \[g=rwx\] \[o=rwx\] filename
#change mod
lsb_release -a
uname -r
```
3. FHS(Filesystem Hierachy Standard)
    (satic|variable)(shareable|unshareable)
    '.'  means this directory
    '..' means above directory
    '-' means last directory
    '~' means curent user's primary directory
    '~someone' means someone's directory
     mkdir -mp m for mod , p for complex directory hierarchies
     rmdir only for empty dirs
     ls -aFhiln


#####/etc/passwd 7fields

| root     | x      | 0    | 0    | root        | root              | bin/bash |
| -------- | ------ | ---- | ---- | ----------- | ----------------- | -------- |
| username | passwd | UID  | GID  | information | working directory | shell    |



#file system
1. inode datablock inodetable
2. dumpe2fs df dd du fdisk mkfs fsck mount mknod e2lable  tune2fs badblocks
3. ext2 ext3 ext4 /proc tmpfs


## JFS (journing file sysytem)

hard link: add a filename, linking to the indentical inode, can't link to a directory

symbolic link: add a new file, the new file is used for recording the linked filename, can be linked to a directory.

# compress

gzip zcat bzip2 bzcat tar

dump restore

 