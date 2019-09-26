WorkerScript.onMessage = function(message){
    let IPUrl = "http://www.geoplugin.net/json.gp"
    
    console.log("Retrieving IP...")
    
    try {
        var httpRequest = new XMLHttpRequest();
        httpRequest.open("GET", IPUrl, false);
        httpRequest.send(null);
        
        var jsonObj = JSON.parse(httpRequest.responseText);
        
        if(jsonObj.geoplugin_countryCode != null) 
            var text = jsonObj.geoplugin_request + " (" + jsonObj.geoplugin_countryCode + ")"
        else
            var text = jsonObj.geoplugin_request
    } catch (err){
        var text = "Unknown"
    }
    
    WorkerScript.sendMessage(text)
}


