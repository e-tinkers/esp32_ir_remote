'use strict';

document.addEventListener("DOMContentLoaded", function(event) {

    const animateIndicator = function() {
        document.getElementById('indicator').style.display='block';
        setTimeout(function(){
            document.getElementById("indicator").style.display = 'none';
        }, 50);
    }

    const sendRequest = function(command, code) {
        return fetch(
          `http://${location.host}/api`,
          {
            method: 'POST',
            body: JSON.stringify({
              command: command,
              code: code
            }),
            headers: {
              'Content-Type': 'application/json'
            }
          }
        );
    }

    const getSensorReading = function() {
      fetch(`http://${location.host}/temperature`)
        .then((resp) => resp.json())
        .then(function(data) {
          document.getElementById('temp-value').innerHTML = data.temperature.toFixed(1);
          document.getElementById('humid-value').innerHTML = data.humidity.toFixed(1);
          document.getElementById('time-value').innerHTML = new Date().toTimeString().substr(0,5);
        });
    }

    getSensorReading();
    setInterval(getSensorReading, 60*1000);

    let promise;
    let targets = document.getElementsByClassName('icons');
    for (let i = 0; i < targets.length; i++) {
      targets[i].addEventListener("click", function(e) {
          const d = e.target.getAttribute('id').split(' ');
          const command = d[0];
          const code = d[1];
          promise = sendRequest(command, code);
          animateIndicator();
      });
    }

});
