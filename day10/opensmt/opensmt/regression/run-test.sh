#!/bin/bash
echo "This is the script for running regression tests"
echo " - date: $(date '+%Y-%m-%d at %H:%M.%S')"
echo " - host name $(hostname -f)"
echo " - script path: $(readlink -f $0)"

opensmt=../opensmt

tmpfolder=log-$(date '+%Y-%m-%d-%H-%M-%S')
mkdir ${tmpfolder}

export outmod=false
export errmod=false
export rtmod=false
tolerance=1.5

for file in $(find . -name '*.smt2' |sort) generic/foo state-dump/bar-00.smt2 state-dump/bar-01.smt2; do
    name=$(basename $file)
    dir=$(dirname $file)

    /usr/bin/time -p -o $tmpfolder/$name.time ${opensmt} $dir/$name > $tmpfolder/$name.out 2>$tmpfolder/$name.err.tmp
    #/usr/bin/time -p -o $tmpfolder/$name.time valgrind --leak-check=full ${opensmt} $dir/$name
    #continue
    grep -v '^;' $tmpfolder/$name.err.tmp > $tmpfolder/$name.err
    diff -q ${tmpfolder}/${name}.out ${dir}/${name}.expected.out
    if [ $? != 0 ]; then
        echo "stdout differs for benchmark $file";
        outmod=true;
    fi
    diff -q ${tmpfolder}/${name}.err ${dir}/${name}.expected.err
    if [ $? != 0 ]; then
        echo "stderr differs for benchmark $file";
        errmod=true;
    fi

    wtime_ref=$(grep "^real" ${dir}/${name}.expected.time |awk '{print $2}')
    utime_ref=$(grep "^user" ${dir}/${name}.expected.time | awk '{print $2}')
    stime_ref=$(grep "^sys" ${dir}/${name}.expected.time | awk '{print $2}')

    wtime=$(grep "^real" ${tmpfolder}/${name}.time |awk '{print $2}')
    utime=$(grep "^user" ${tmpfolder}/${name}.time | awk '{print $2}')
    stime=$(grep "^sys"  ${tmpfolder}/${name}.time | awk '{print $2}')

    if [[ $(echo "${wtime_ref} > 1" |bc -l) -eq 1 ]]; then
        if [[ $(echo "${wtime_ref} * ${tolerance} < ${wtime}" | bc -l) -eq 1 ]]; then
            rtmod=true;
            echo "wall time too high for benchmark $file";
        fi
        if [[ $(echo "${wtime} * ${tolerance} < ${wtime_ref}" | bc -l) -eq 1 ]]; then
            rtmod=true;
            echo "wall time too low for benchmark $file";
        fi
    fi

    if [[ $(echo "${utime_ref} > 1" |bc -l) -eq 1 ]]; then
        if [[ $(echo "${utime_ref} * ${tolerance} < ${utime}" | bc -l) -eq 1 ]]; then
            rtmod=true;
            echo "user time too high for benchmark $file";
        fi
        if [[ $(echo "${utime} * ${tolerance} < ${utime_ref}" | bc -l) -eq 1 ]]; then
            rtmod=true;
            echo "user time too low for benchmark $file";
        fi
    fi

    if [[ $(echo "${stime_ref} > 1" |bc -l) -eq 1 ]]; then
        if [[ $(echo "${stime_ref} * ${tolerance} < ${stime}" | bc -l) -eq 1 ]]; then
            rtmod=true;
            echo "sys time too high for benchmark $file";
        fi
        if [[ $(echo "${stime} * ${tolerance} < ${stime_ref}" | bc -l) -eq 1 ]]; then
            rtmod=true;
            echo "sys time too low for benchmark $file";
        fi
    fi
done
echo "Stdout differs: ${outmod}, stderr differs: ${errmod}, run time differs: ${rtmod}"


if [[ ${outmod} == true || ${errmod} == true || ${rtmod} == true ]]; then
    echo "There were anomalies: check logs in ${tmpfolder}"
    exit 1
else
    rm -rf ${tmpfolder}
fi

if [ -z "${OSMT_INSTALLDIR}" ]; then
    echo "Skipping the check for compilation against the library. "
    echo "Please set OSMT_INSTALLDIR."
else
    echo "Testing linkage against the libraries"
    cd linkage;
    g++ -std=c++11 -o test test.cc -lopensmt2 -lgmp -lgmpxx -lz \
        -lreadline -L${OSMT_INSTALLDIR}/lib \
        -I${OSMT_INSTALLDIR}/include > /dev/null 2>&1 \
            || echo "Failed to link test.cc"
    LD_LIBRARY_PATH=${OSMT_INSTALLDIR}/lib ./test 2>&1 |grep '^unsat' >/dev/null || echo "Failed to run ./test"
    gcc -o test_c test_c.c -lopensmt2c -lgmp -lgmpxx -lz -lreadline \
        -L${OSMT_INSTALLDIR}/lib \
        -I${OSMT_INSTALLDIR}/include > /dev/null 2>&1 \
            || echo "Failed to link test_c.c"
    LD_LIBRARY_PATH=${OSMT_INSTALLDIR}/lib ./test_c 2>&1 |grep '^unsat' >/dev/null || echo "Failed to run ./test"
fi
