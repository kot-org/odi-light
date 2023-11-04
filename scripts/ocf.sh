#!/bin/bash

src_dir="../src"

ocf_path="../odi-ocf.c"

config_path="../config.h"
config_default_path="../config_default.h"

c_files=$(find "$src_dir" -name "*_g.c")

rm -f $ocf_path

if [ ! -f "$config_path" ]; then
  cp $config_default_path $config_path
fi

echo "#ifndef ODI_OFC" >> "$ocf_path"
echo "#define ODI_OFC" >> "$ocf_path"
echo "" >> "$ocf_path"

echo "#include \"$(realpath "$config_path")\"" >> "$ocf_path"

for c_file in $c_files; do
  echo "#include \"$(realpath "$c_file")\"" >> "$ocf_path"
done

echo "" >> "$ocf_path"
echo "#endif // ODI_OFC" >> "$ocf_path"

echo "OCF (One C File) created with success : $ocf_path"
