// var http = require('http');

// http.createServer(function (req, res) {
//   res.writeHead(200, {'Content-Type': 'text/html'});
//   res.end('Hello World!');
// }).listen(8080);

var http = require('http'),
    url = require('url'),
    mongo = require('mongodb');
var mongoclient = mongo.MongoClient;
var mongourl = "mongodb://localhost:27017/";
var temp_db;
mongoclient.connect(mongourl, function(err, db){
    if(err) throw err;
    temp_db = db.db("temp_db");
    console.log("DB created");
    temp_db.createCollection("temp_data_coll", function (err, res) {
        if(err) throw err;
        console.log("collection created");
        db.close();
    });
});

http.createServer(function (req, res) {
    var query = url.parse(req.url,true).query;
    var sensor_name = query.sensor_number;
    var temp = parseInt(query.temperature);
    var date = new Date().toUTCString();
    var document = {'sensor_name':sensor_name,'temp':temp,'date':date}
    console.log(document);
    mongoclient.connect(mongourl, function(err, db){
        if(err) throw err;
        console.log("DB created");
        temp_db = db.db("temp_db");
        temp_db.collection("temp_data_coll").insertOne(document, function (err, res) {
            if(err) throw err;
            console.log("document inserted");
            db.close();
        });
    });

    res.end(JSON.stringify(query));
    console.log(JSON.stringify(query));
}).listen(8080);
console.log("Server running at http://localhost:8080/"+new Date().toUTCString());