#!/bin/bash

# Define the directory to be zipped
dir_to_zip="/home/compleks/tester/lockedfile.txt"

# Define the name of the zip file
zip_file_name="/home/compleks/tester/locked_folder.zip"

# Define the password to be used for the zip file
zip_password="mysecret"

# Create the zip file with password protection
zip -r -P "$zip_password" "$zip_file_name" "$dir_to_zip"

#remove file
rm "$dir_to_zip"  
echo "Zip file created: $zip_file_name"

