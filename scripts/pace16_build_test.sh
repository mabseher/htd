#!/bin/bash

STORAGE_DIRECTORY=`dirname "$(readlink -f "$0")"`

TEST_DIRECTORY="${STORAGE_DIRECTORY}/pace16_build_test"

mkdir -p "${TEST_DIRECTORY}"
mkdir -p "${TEST_DIRECTORY}/instances"
mkdir -p "${TEST_DIRECTORY}/validator"

wget -O "${TEST_DIRECTORY}/instances.tar.gz" "http://bit.ly/pace16-tw-instances-20160307"

wget -O "${TEST_DIRECTORY}/validator.zip" "https://github.com/holgerdell/td-validate/archive/master.zip"

tar --directory "${TEST_DIRECTORY}/instances" --strip-components=3 -xzf "${TEST_DIRECTORY}/instances.tar.gz" "pace16-tw-instances-20160307/tw-exact/hard"

unzip -u -d "${TEST_DIRECTORY}/validator" "${TEST_DIRECTORY}/validator.zip"

bash -c "cd \"${TEST_DIRECTORY}/validator/td-validate-master\" && make && make test"

HTD="${STORAGE_DIRECTORY}/htd_gr2td_mindegree_iterative_100_20.sh"
VALIDATOR="${TEST_DIRECTORY}/validator/td-validate-master/td-validate"
VALIDATION_INSTANCE_FOLDER="${TEST_DIRECTORY}/instances"

echo "Instance,Vertices,Seed,Width,Nodes,Time,Memory"

for INSTANCE in `find "$VALIDATION_INSTANCE_FOLDER/" -type f -name "*.gr" -exec ls {} \; 2> /dev/null | awk -F/ '{print $(NF-2)"/"$(NF-1)"/"$(NF)}' | sort`
do
    for ITERATION in {1..10..1}
    do
        eval "\time --format=\"%U %M\" $HTD -s ${ITERATION} < \"${STORAGE_DIRECTORY}/${INSTANCE}\"" > "${TEST_DIRECTORY}/tmp.out" 2> "${TEST_DIRECTORY}/tmp.err"
    
        eval "$VALIDATOR $INSTANCE \"${TEST_DIRECTORY}/tmp.out\"" 2> "${TEST_DIRECTORY}/tmp.res"

        STATE=`cat "${TEST_DIRECTORY}/tmp.res"`

        if [ "x${STATE}x"="xvalidx" ]
        then
            cat "${TEST_DIRECTORY}/tmp.out" | grep -v "c" > "${TEST_DIRECTORY}/tmp2.out"

            mv "${TEST_DIRECTORY}/tmp2.out" "${TEST_DIRECTORY}/tmp.out"

            TIME=`cut -d' ' -f1 "${TEST_DIRECTORY}/tmp.err"`
            MEMORY=`cut -d' ' -f2 "${TEST_DIRECTORY}/tmp.err"`
    
            NODES=`head -n1 "${TEST_DIRECTORY}/tmp.out" | cut -d' ' -f3`
            WIDTH=`head -n1 "${TEST_DIRECTORY}/tmp.out" | cut -d' ' -f4`
            VERTICES=`head -n1 "${TEST_DIRECTORY}/tmp.out" | cut -d' ' -f5`

            echo "\"$INSTANCE\",$VERTICES,$ITERATION,$WIDTH,$NODES,$TIME,$MEMORY"
        else
            echo "ERROR: Decomposition for instance '${INSTANCE}' is invalid!"

            exit 1
        fi

        rm "${TEST_DIRECTORY}/tmp.out"
        rm "${TEST_DIRECTORY}/tmp.err"
        rm "${TEST_DIRECTORY}/tmp.res"
    done
done

echo ""

HTD="${STORAGE_DIRECTORY}/htd_gr2td_minfill_iterative_100_20.sh"

echo "Instance,Vertices,Seed,Width,Nodes,Time,Memory"

for INSTANCE in `find "$VALIDATION_INSTANCE_FOLDER/" -type f -name "*.gr" -exec ls {} \; 2> /dev/null | awk -F/ '{print $(NF-2)"/"$(NF-1)"/"$(NF)}' | sort`
do
    for ITERATION in {1..10..1}
    do
        eval "\time --format=\"%U %M\" $HTD -s ${ITERATION} < \"${STORAGE_DIRECTORY}/${INSTANCE}\"" > "${TEST_DIRECTORY}/tmp.out" 2> "${TEST_DIRECTORY}/tmp.err"
    
        eval "$VALIDATOR $INSTANCE \"${TEST_DIRECTORY}/tmp.out\"" 2> "${TEST_DIRECTORY}/tmp.res"

        STATE=`cat "${TEST_DIRECTORY}/tmp.res"`

        if [ "x${STATE}x"="xvalidx" ]
        then
            cat "${TEST_DIRECTORY}/tmp.out" | grep -v "c" > "${TEST_DIRECTORY}/tmp2.out"

            mv "${TEST_DIRECTORY}/tmp2.out" "${TEST_DIRECTORY}/tmp.out"

            TIME=`cut -d' ' -f1 "${TEST_DIRECTORY}/tmp.err"`
            MEMORY=`cut -d' ' -f2 "${TEST_DIRECTORY}/tmp.err"`
    
            NODES=`head -n1 "${TEST_DIRECTORY}/tmp.out" | cut -d' ' -f3`
            WIDTH=`head -n1 "${TEST_DIRECTORY}/tmp.out" | cut -d' ' -f4`
            VERTICES=`head -n1 "${TEST_DIRECTORY}/tmp.out" | cut -d' ' -f5`

            echo "\"$INSTANCE\",$VERTICES,$ITERATION,$WIDTH,$NODES,$TIME,$MEMORY"
        else
            echo "ERROR: Decomposition for instance '${INSTANCE}' is invalid!"

            exit 1
        fi

        rm "${TEST_DIRECTORY}/tmp.out"
        rm "${TEST_DIRECTORY}/tmp.err"
        rm "${TEST_DIRECTORY}/tmp.res"
    done
done

rm -r "${TEST_DIRECTORY}"
