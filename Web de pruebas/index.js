  var wsUri = "ws://localhost:3344";
  websocket = new WebSocket(wsUri);
  var output;
  var recivedMessage;
  var parser;
  var xmlDoc;
  $(function(){
    $("#modelo").chained("#marca");
   });

  function init()
  {
    error = document.getElementById("error");
    testWebSocket();
  }

  function testWebSocket()
  {
   
    websocket.onopen = function(evt) { onOpen(evt) };
    websocket.onclose = function(evt) { onClose(evt) };
    websocket.onmessage = function(evt) { onMessage(evt) };
    websocket.onerror = function(evt) { onError(evt) };
  }
  function reqTelefonos()
  {
    var message= '<?xml version="1.0" encoding="UTF-8"?> <!DOCTYPE telefonos SYSTEM "modelos_request.dtd">'+
                 '<document><header><tipo>request_modelos</tipo></header>'+
                 '<payload></payload>'+
                 '</document>';
    websocket.send(message);
  }


  function onOpen(evt)
  {
    
    
  }

  function onClose(evt)
  {
    writeToScreen("DISCONNECTED");
  }

  function onMessage(evt)
  {
    recivedMessage = evt.data;

    console.log(evt.data);
    parser = new DOMParser();
    xmlDoc = parser.parseFromString(recivedMessage,"text/xml");

    if (xmlDoc.getElementsByTagName("tipo")[0].childNodes[0].nodeValue = "modelos_result") {
      for (let i = 0; i < xmlDoc.getElementsByTagName("dispositivo").length; i++) {
       // var marca = xmlDoc.getElementsByTagName("dispositivo")[i].childNodes[0].childNodes[0].nodeValue;
        var marca = xmlDoc.getElementsByTagName("marca")[i].childNodes[0].nodeValue;
        var newOption = document.createElement("option")
        newOption.value = marca;
        newOption.innerHTML = marca ;
        
           document.getElementById("marca").append(newOption)     

           //TODO: que cuando seleccionemos una marca nos carge los modelos correspondientes
        for (let j = 0; j < xmlDoc.getElementsByTagName("dispositivo")[0].children.length -1; j++) {
          
          var modelo = xmlDoc.getElementsByTagName("dispositivo")[0].children[j+1].textContent;

          var newOption = document.createElement("option")
          newOption.value = modelo;
          newOption.innerHTML = modelo;
          newOption.className = marca;
          document.getElementById("modelo").append(newOption); 

        }


      }

    }



    //writeToScreen('<span style="color: blue;">RESPONSE: ' + evt.data+'</span>');
    websocket.close();
  }

  function onError(evt)
  {
    writeError('<span style="color: red;">ERROR:</span> ' + evt.data);
  }

  function doSend(message)
  {
    
    websocket.send(message);
  }

  function writeError(message)
  {
      error.innerHTML = message;
    
  }

  /*
  QString XmlHandler::readContentOfTag( QString xml ,QString nombreTag)
{

QDomDocument doc;
doc.setContent(xml);
QDomNodeList list = doc.elementsByTagName(nombreTag);
QString model= list.at(0).toElement().text();
return model;
}

  */
  window.addEventListener("load", init, false);
