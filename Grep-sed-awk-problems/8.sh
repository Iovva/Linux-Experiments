cat ps.fake | awk '{if($1 ~ "^r")print $1}' | sort | uniq | sed -r 's/[aeiou]/&&/g'