grep -E '^root' ps.fake | awk '{print $6}' | sort | uniq