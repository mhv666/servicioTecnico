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
    
    //TODO: ejecutar funcion despues de hacer login y no al abrir el Websocket
    //reqTelefonos();
    

    
}
function onClose(evt) {
    
}
function onMessage(evt) {
    recivedMessage = evt.data;
    var tipo = readTagXml(recivedMessage,"tipo");
    switch (tipo) {
    case "modelos_result":
        buscarMarcas(); 
        break;
    case "login_result":
        if(isValidUser(recivedMessage))
        {
            borrarContenidoLogin();
            crearFormularioRma();
            reqTelefonos();
            //TODO: una vez validado borrar contenido de content y añadir el nuevo contenido con los campos necesarios
            break;
        }else
        {
            alert("Usuario o password incorrecto");

        }
        break;
    default:
        break;
    }
   

    
    
    
}
function onError(evt) {
    writeError("<span style='color: red;'>ERROR:</span> " + evt.data);
}
function writeError(message) {
    error.innerHTML = message;

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

            document.getElementById("marca").append(newOption);
                  
        } //end for
    } // end if
}
function buscaModelos(marcaBuscar)
{
    parser = new DOMParser();
    xmlDoc = parser.parseFromString(recivedMessage, "text/xml");
    var tipo = xmlDoc.getElementsByTagName("tipo")[0].childNodes[0].nodeValue;
    if ( tipo == "modelos_result") {
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
    buscaModelos(document.getElementById("marca").value);
}
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
function crearNuevaOrdenXml(){
//https://stackoverflow.com/questions/14340894/create-xml-in-javascript
//https://developer.mozilla.org/en-US/docs/Web/API/Document_object_model/How_to_create_a_DOM_tree
    var doctypeXml = document.implementation.createDocumentType("rma","SYSTEM","newRma.dtd");
    var xmlToSend = document.implementation.createDocument("", "", doctypeXml);
    
    
    var rma = xmlToSend.createElement("rma");
    var headerElement = xmlToSend.createElement("header");
    var payloadElement = xmlToSend.createElement("payload");

    //hijos de header
    var tipoElement = xmlToSend.createElement("tipo");
    tipoElement.innerHTML = "newRma";
    headerElement.appendChild(tipoElement);

    //hijos de payload
    var userElement = xmlToSend.createElement("user");
    payloadElement.appendChild(userElement);
    var telefonoElement = xmlToSend.createElement("telefono");
    payloadElement.appendChild(telefonoElement);
    var tiendaElement = xmlToSend.createElement("tienda");
    payloadElement.appendChild(tiendaElement);

    var aSolucionarElement = xmlToSend.createElement("aSolucionar");
    payloadElement.appendChild(aSolucionarElement);

    //Hijos de user
    var nombreElement = xmlToSend.createElement("nombre");
    nombreElement.innerHTML = document.getElementById("nombreUser").value;
    var apellidoElement = xmlToSend.createElement("apellido");
    apellidoElement.innerHTML = document.getElementById("apellidoUser").value;
    var numTelefonoElement = xmlToSend.createElement("numTelefono");
    numTelefonoElement.innerHTML = document.getElementById("numTlfUser").value;
    userElement.appendChild(nombreElement);
    userElement.appendChild(apellidoElement);
    userElement.appendChild(numTelefonoElement);

    //Hijos de telefono
    var marcaElement = xmlToSend.createElement("marca");
    marcaElement.innerHTML = document.getElementById("marca").value;
    var modeloElement = xmlToSend.createElement("modelo");
    modeloElement.innerHTML = document.getElementById("modelo").value;

    telefonoElement.appendChild(marcaElement);
    telefonoElement.appendChild(modeloElement);

    //hijos de aSolucionar
    aSolucionarElement.innerHTML = document.getElementById("descripcion").value;
    
    //Hijos de tienda
    var idTienda = xmlToSend.createElement("idTienda");
    idTienda.innerHTML = document.getElementById("idTienda").value;
    tiendaElement.appendChild(idTienda);

    rma.appendChild(headerElement);
    rma.appendChild(payloadElement);
   
    xmlToSend.appendChild(rma);

    var xmlSerializer = new XMLSerializer();
    var stringOfXml = xmlSerializer.serializeToString(xmlToSend);
    enviarXml(stringOfXml);
    
    

}
function enviarXml(xml)
{
    
    console.log(xml);
    websocket.send(xml);
}
function crearXmlLogin()
{
    var doctypeXml = document.implementation.createDocumentType("login","SYSTEM","login.dtd");
    var xmlToSend = document.implementation.createDocument("", "", doctypeXml);
    var login =xmlToSend.createElement("login");
    var headerElement = xmlToSend.createElement("header");
    var payloadElement = xmlToSend.createElement("payload");
    //hijos de header
    var tipoElement = xmlToSend.createElement("tipo");
    tipoElement.innerHTML = "loginRequest";
    headerElement.appendChild(tipoElement);
    //hijos de payload
    var usernameElement = xmlToSend.createElement("username");
    usernameElement.innerHTML = document.getElementById("nombreUser").value;
    var passwordElement = xmlToSend.createElement("password");
    passwordElement.innerHTML =document.getElementById("password").value;
    payloadElement.appendChild(usernameElement);
    payloadElement.appendChild(passwordElement);
    //hijos de login(root)
    login.appendChild(headerElement);
    login.appendChild(payloadElement);



    xmlToSend.appendChild(login);
    
    var xmlSerializer = new XMLSerializer();
    var xmlLogin = xmlSerializer.serializeToString(xmlToSend);
    
    enviarXml(xmlLogin); 
}
function login(){
    crearXmlLogin();
   
}
function crearFormularioRma(){
    var contentElement = document.getElementById("content");
    var idTienda = readTagXml(recivedMessage,"idTienda");
    var htmlToAdd ='<div class="contact"> <h3>Email us</h3>  <form action="">'  
                  +'<p> <label for="nombreUser">Nombre</label> <input type="text" name="name" id="nombreUser">'
                  +'</p><p><label for="apellidoUser">Apellido/s</label><input type="text" name="name" id="apellidoUser">'
                  +'</p><p>    <label for="numTlfUser">Numero de telefono</label>    <input type="text" name="name" id="numTlfUser">'
                  +' </p><p><label for="marca">Marca</label><select class="dispositivo" id="marca" onchange="rellenarModelos()">'
                  +'    <option id="sel_marca" value="null">Seleccione una:</option> </select> </p>'
                  +'<p class="full"><label for="modelo">Modelo</label><div class="select"><select class="dispositivo" id="modelo">'
                  +'    <option value="null">Seleccione uno:</option></select></div></p><p class="full"><h4 id="error">hola</h4></p><p> '
                  +'    <label for="idTienda">Id Tienda</label><input type="text"  name="name" value="'+ idTienda +' "id="idTienda" disabled></p><p class="full">                  '
                  +'    <label for="descripcion">Descripcion</label><textarea name="Descripcion" rows="5" id="descripcion"></textarea></p>                  '
                  +'    <p class="full"><button type="button" onclick="enviarXml()">Enviar</button></p>  </form></div>';
    
    contentElement.innerHTML = htmlToAdd;
}

function borrarContenidoLogin(){
    var contactElements =   document.getElementsByClassName("contact");
    contactElements[0].remove();
}
function readTagXml(xml,tagToRead)
{   
    
    parser = new DOMParser();
    xmlDoc = parser.parseFromString(xml, "text/xml");
    var tipo = xmlDoc.getElementsByTagName(tagToRead)[0].childNodes[0].nodeValue;
    return tipo;
}
function isValidUser(xml)
{
    parser = new DOMParser();
    xmlDoc = parser.parseFromString(xml, "text/xml");
    var isValid = xmlDoc.getElementsByTagName("isValid")[0].childNodes[0].nodeValue;
    if(isValid != "true") return false;
    return true;
}
window.addEventListener("load", init, false);