# Usage 

## Using the driver directly

The Driver has the options to set the min and max value to get the value between them

To insert the driver you can use the script provided with the repo

>\# ./insert.sh

Then you will see the character driver at
>\# ls /dev/random_char

**Set Limit**
> \# echo "<min> <max>" > /dev/random_char

**Get Value**
>\# cat /dev/random_char

Example 

``` Shell
echo "10 15" > /dev/random_char 
cat /dev/random_char 
Output:
14
```

## Using the test app
Test app provides example on how to use the test application at [Test Folder](../test/)

You can use the structure [rng_data_t](../inc/rng_custom.h) to set the min and max value and get the value back form driver.

``` shell
# ./bin/test_rng 
Value 11
```