#!/bin/bash
#get jdk bits
JAVA_VERSION=`java -version 2>&1 |awk 'NR==3{ gsub(/"/,""); print $2 }'`'""")};'
#echo ${JAVA_VERSION:0:2};
bit=${JAVA_VERSION:0:2};
#judge device type and jdk bits
if [ $1  == "0" ]
then 
	#echo "choice sjj1507"
	 if [ ${bit} == "64" ]
		    then 
				#echo "sjj1507 jdk64"
				cp ./sjj1507/linux_x64/libTass*.so /usr/lib64/
				cp ./sjj1507/linux_x64/libTass*.a /usr/lib64/
                        cp ./sjj1507/linux_x64/*.ini /usr/lib64/
                                echo "copy success"
			else
			      #echo "sjj1507 jdk32"
				cp ./sjj1507/linux_x86/libTass*.so /usr/lib/
				cp ./sjj1507/linux_x86/libTass*.a /usr/lib/
                        cp ./sjj1507/linux_x86/*.ini /usr/lib/
                                echo "copy success"
	 fi
elif [ $1 == "1" ]
then 
	#echo "choice sjj1313"
	if [ ${bit} == "64" ]
		  then 
                    #echo "sjj1313 jdk 64"
			  cp ./sjj1313/linux_x64/libTass*.so /usr/lib64/
			  cp ./sjj1313/linux_x64/libTass*.a /usr/lib64/
                    cp ./sjj1313/linux_x64/*.ini /usr/lib64/
                                  echo "copy success"
		  else
		        #echo "sjj1313 jdk 32"
		        cp ./sjj1313/linux_x32/libTass*.so /usr/lib/
			  cp ./sjj1313/linux_x32/libTass*.a /usr/lib/
                    cp ./sjj1313/linux_x32/*.ini /usr/lib/
                                  echo "copy success"

    fi
else 
	echo "command line arguments is Invalid"
	exit -1
fi
