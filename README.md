# impala-udf-test

udf for impala

## Build

```sh
mkdir impala-udf-test-debug
cd impala-udf-test-debug
cmake ../impala-udf-test && make
```

## Add My UDF Functions

For Example:

```
$ hdfs dfs -put -f libmyudf.so /tmp/
$ impala-shell -i impala-host;
> create database myudfs;
> use myudfs;
> create function strcat(string, string...) returns string location '/tmp/libmyudf.so' Symbol='Concat';
```


