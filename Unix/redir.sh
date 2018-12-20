#!/bin/bash

function redir {
    local current_dir 
    local parent_dir 
    local work_dir
    work_dir=$1
    cd ${work_dir}
    if [${work_dir} eq  "/"]
    then
        current_dir=""
    else
        current_dir=$(pwd)
    fi

    for dirlist in $(ls ${current_dir})
    do
        if test -d ${dirlist};
            then cd ${dirlist}
            redir ${current_dir}/${dirlist}
            cd ..
        else
            echo -n ${current_dir}/${dirlist}
            cat ${current_dir}/${dirlist} | gawk '/#include/ {print $0}'
        fi
    done
}

if test -d $1
then
    redir $1
else if test -f $1
then
    ls $1
    exit 1
else
    exit 2
fi
fi
