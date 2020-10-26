const express = require('express');
var exphbs  = require('express-handlebars');
var bodyParser = require('body-parser');
var admin = require('firebase-admin');
const app = express();

app.use(bodyParser.urlencoded({ extended: false }));
app.use(bodyParser.json());
app.engine('handlebars', exphbs());
app.set('view engine', 'handlebars');

var serviceAccount = require("./nodefirebase-57412-firebase-adminsdk-kgxbi-2b5eca591e.json");

admin.initializeApp({
credential: admin.credential.cert(serviceAccount),
databaseURL: "https://nodefirebase-57412.firebaseio.com"
});

var db = admin.database();
app.get('/', function (req, res) {
    res.render('home',{title:"Bienvenido"});
});
app.get('/lista', function (req, res) {
    var li;
    db.ref("Botones").on("value", function(snapshot){
        li = snapshot.val();
        res.render('lista',{title:"Estas en lista xD" ,desc:"Yo escribo aqui",list: li});
    });
});

app.post('/add', (req, res) =>{
    var x = req.body.client;
    var nuevoDoc = {
        boton1: req.body.btn1,
        boton2: req.body.btn2,
        boton3: req.body.btn3,
        cliente: req.body.client
    }
    x = x.replace('.','').replace('.','').replace('.','').replace('.','');
    db.ref("Botones/"+ x ).set(nuevoDoc);
    console.log(req.body);
    res.end(x);
});




app.post('/guardar', function (req, res) {
    console.log(req.body);
    var newUser = {
        email: req.body.email,
        pass: req.body.pass
    }
    db.ref("Usuarios").push(newUser);
    res.render('home',{title: req.body.email});
});

app.listen(3000,function(){
    console.log('Server corriendo en el puerto 3000')
});