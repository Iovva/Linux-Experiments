sed -r 's/ pts.+\s\s[0-9]\s/ /g' last.fake | sed -r 's/:.+//g' | grep -E ' 2[34]'| sed -r 's/ .+//g' | sort | uniq