var express = require('express');
var app = express();
var port = 5000;

var path = require('path');

var moment = require('moment');

app.use(express.static(path.join(__dirname, 'esp8266_binfile')));

app.get('/', function(req, res){
  res.status(200).jsonp({status:"ready"});
});

app.get('/ota/:version', function(req, res){
  switch (true) {
    case req.params.version == 'normal':
      console.log('sending normal LED blink firmware OTA');
      res.sendFile(path.join(__dirname + '/esp8266_binfile/normalblink.ino.d1_mini.bin'));
      break;
    case req.params.version == 'special':
      console.log('sending special LED blink firmware OTA');
      res.sendFile(path.join(__dirname + '/esp8266_binfile/specialblink.ino.d1_mini.bin'));
      break;
    default:
      //..
  }
});

app.listen(port, function(){
  console.log('OTA protocol for ESP8266 firmware update started port : ' + port);
});
