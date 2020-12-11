const express = require('express');
var bodyParser = require('body-parser');
var admin = require('firebase-admin');
const app = express();

app.use(bodyParser.urlencoded({ extended: false }));
app.use(bodyParser.json());

var serviceAccount = require("./nodefirebase-57412-firebase-adminsdk-kgxbi-2b5eca591e.json");

admin.initializeApp({
credential: admin.credential.cert(serviceAccount),
databaseURL: "https://nodefirebase-57412.firebaseio.com"
});

var db = admin.database();
app.get('/', async (req, res) => {
    var li;
    await db.ref("servos").once("value", function(snapshot){
        li = snapshot.val();
    });
    res.send(li)
});


app.post('/', async (req, res) =>{
    var d = new Date();
    let day = d.getDate();
    let month = d.getMonth();
    let year = d.getFullYear();
    let hour = d.getHours()
    let min = d.getMinutes()
    let seg = d.getSeconds()
    let mil = d.getMilliseconds()
    let date = year + "-" + month + "-" + day
    let time = hour + ":" + min +":" + seg + ":"+mil
    var nuevoDoc = {
        servo: req.body.grad,
        date,
        time
    }
    await db.ref("servos" ).push(nuevoDoc);
    res.end("Done");
});


app.listen(4003,function(){
    console.log('Server corriendo en el puerto 3000')
});
