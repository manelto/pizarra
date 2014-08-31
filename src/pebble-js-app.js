Pebble.addEventListener("Ready",
  function(e) {
    console.log("PebbleKit JS Listo!");
  }
);

Pebble.addEventListener("showConfiguration",
  function(e) {
    //Load the remote config page
    Pebble.openURL("https://dl.dropboxusercontent.com/u/97672409/op_pebble.html");
  }
);

Pebble.addEventListener("webviewclosed",
  function(e) {
    //Get JSON dictionary
    var configuration = JSON.parse(decodeURIComponent(e.response));
    console.log("Configuration window returned: " + JSON.stringify(configuration));
 
    //Send to Pebble, persist there
    Pebble.sendAppMessage(
      {"KEY_INVERT": configuration.invert,"KEY_IDIOMA": configuration.idioma},
      function(e) {
        console.log("Sending settings data..." + e.data.transactionId);
      },
      function(e) {
        console.log("Settings feedback failed!");
      }
    );
  }
);