
import requests
import json
from pyspark.sql import SparkSession
from pyspark.sql import Row
from pyspark.sql.types import StringType, StructType, StructField

r = requests.get('http://144.202.34.148:4003')
response = r.text
print("toda",response)

print("inserta fecha inicial")
fechainicial = input()
print("fecha inicial es",fechainicial)
print("inserta fecha final")
fechafinal = input()
print("fecha final es",fechafinal)

    # $example on:init_session$
spark = SparkSession \
    .builder \
    .appName("Python Spark SQL basic example") \
    .config("spark.some.config.option", "some-value") \
    .getOrCreate()
    # $example off:init_session$

sc = spark.sparkContext


# Alternatively, a DataFrame can be created for a JSON dataset represented by
# an RDD[String] storing one JSON object per string
jsonStrings = [response]
otherPeopleRDD = sc.parallelize(jsonStrings)
otherPeople = spark.read.json(otherPeopleRDD)

otherPeople.printSchema()
otherPeople.createOrReplaceTempView("servo")

query = "select avg(servo.servo) from servo where date >= '" + fechainicial + "' and date <= '" + fechafinal+"'"
otherPeople.printSchema()
otherPeople.createOrReplaceTempView("servo")
teenager = spark.sql(query)
teenager.show(100)

#2019-11-10 22:6:24:831
#2020-11-10 22:6:24:831

spark.stop()
