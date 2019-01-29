  var wsUri = "ws://localhost:3344";
  websocket = new WebSocket(wsUri);
  var output;

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
    writeToScreen('<span style="color: blue;">RESPONSE: ' + evt.data+'</span>');
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

  window.addEventListener("load", init, false);
