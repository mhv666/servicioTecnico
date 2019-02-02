var wsUri = "ws://localhost:3344";
var websocket;
var recivedMessage;
var parser;
var xmlDoc;
var error;
function init() {
    error= document.getElementById("error");
    
    testWebSocket();
    

}

function testWebSocket() {

    websocket = new WebSocket(wsUri);

    websocket.onopen = function (evt) {
        onOpen(evt);
    };
    websocket.onclose = function (evt) {
        onClose(evt);
    };
    websocket.onmessage = function (evt) {
        onMessage(evt);
    };
    websocket.onerror = function (evt) {
        onError(evt);
    };
}

function reqTelefonos() {
    var message = '<?xml version="1.0" encoding="UTF-8"?> <!DOCTYPE telefonos SYSTEM "modelos_request.dtd">' +
                  '<document><header><tipo>request_modelos</tipo></header>' +
                  '<payload></payload>' +
                  '</document>';
    websocket.send(message);
}


function onOpen(evt) {
    reqTelefonos();
}

function onClose(evt) {
    
}

function onMessage(evt) {
    recivedMessage = evt.data;

    buscarMarcas();
    console.log(evt.data);
}

function buscarMarcas()
{
    parser = new DOMParser();
    xmlDoc = parser.parseFromString(recivedMessage, "text/xml");

    document.getElementById("marca").append(newOption);


    if (xmlDoc.getElementsByTagName("tipo")[0].childNodes[0].nodeValue == "modelos_result") {
        var lengthDispositivo = xmlDoc.getElementsByTagName("dispositivo").length;
        for (let i = 0; i < lengthDispositivo; i++) {
        // var marca = xmlDoc.getElementsByTagName("dispositivo")[i].childNodes[0].childNodes[0].nodeValue;
            var marca = xmlDoc.getElementsByTagName("marca")[i].childNodes[0].nodeValue;
            var newOption = document.createElement("option");
            newOption.value = marca;
            newOption.innerHTML = marca;

            document.getElementById("marca").append(newOption)
                  
        } //end for
    } // end if
}
  
  
function buscaModelos(marcaBuscar)
{
    parser = new DOMParser();
    xmlDoc = parser.parseFromString(recivedMessage, "text/xml");


    
                



    if (xmlDoc.getElementsByTagName("tipo")[0].childNodes[0].nodeValue == "modelos_result") {
        var lengthDispositivo = xmlDoc.getElementsByTagName("dispositivo").length;
        borrarElementosEnModelos();
        for (let i = 0; i < lengthDispositivo; i++) {
            // var marca = xmlDoc.getElementsByTagName("dispositivo")[i].childNodes[0].childNodes[0].nodeValue;
            var marca = xmlDoc.getElementsByTagName("marca")[i].childNodes[0].nodeValue;

            
                
            if (marca == marcaBuscar)
            {

                var modelos = [];
                modelos = document.getElementsByXPath("/document/payload/dispositivos/dispositivo[" + (i + 1) + "]/modelo", xmlDoc);
                var newOption = document.createElement("option");
                newOption.value = "null";
                newOption.innerHTML = "Elija el modelo";
                document.getElementById("modelo").append(newOption);
                for (let j = 0; j < modelos.length; j++) {
                    newOption = document.createElement("option");
        
                    newOption.value = modelos[j].firstChild.textContent;
                    newOption.innerHTML = modelos[j].firstChild.textContent;
                    //newOption.className = marca;
                    
                    document.getElementById("modelo").append(newOption);
        
                }
      
                break;
            } // end  if
                      
        } //end for
    } // end if
    

}



function onError(evt) {
    writeError("<span style='color: red;'>ERROR:</span> " + evt.data);
}

function doSend(message) {

    websocket.send(message);
}

function writeError(message) {
    error.innerHTML = message;

}

document.getElementsByXPath = function (xpath, contextNode) {
    var xpathResult;
    if (contextNode === undefined) {
        xpathResult = document.evaluate(xpath, document, null, XPathResult.ANY_TYPE, null);
    } else {
        xpathResult = contextNode.evaluate(xpath, contextNode, null, XPathResult.ANY_TYPE, null);
    }
    var array = [];
    var element;
    element = xpathResult.iterateNext();
    while (element) {
        array[array.length] = element;
        element = xpathResult.iterateNext();
    }
    return array;
};

document.getElementByXPath = function (xpath, contextNode) {
    var xpathResult;
    if (contextNode === undefined) {
        xpathResult = document.evaluate(xpath, document, null, XPathResult.ANY_TYPE, null);
    } else {
        xpathResult = contextNode.evaluate(xpath, contextNode, null, XPathResult.ANY_TYPE, null);
    }
    return xpathResult.iterateNext();
};

// eslint-disable-next-line
function rellenarModelos()
{
    //alert(document.getElementById("marca").value);
    buscaModelos(document.getElementById("marca").value);
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
function borrarElementosEnModelos()
{
    var modelosAnteriores = document.getElementById("modelo");                   
    var length = modelosAnteriores.options.length;

    for(var i = length - 1 ; i >= 0 ; i--)
    {
        modelosAnteriores.remove(i);
    }

}
// eslint-disable-next-line
function enviarNuevaOrdenXml(){
//https://stackoverflow.com/questions/14340894/create-xml-in-javascript
//https://developer.mozilla.org/en-US/docs/Web/API/Document_object_model/How_to_create_a_DOM_tree

}
window.addEventListener("load", init, false);