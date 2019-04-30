var myCharacteristic;

function onStartButtonClick() {
  let serviceUuid = 0x181a;
  let characteristicUuid = 0x2a6e;

  console.log('Suche nach Bluetooth-Geräten.');
  navigator.bluetooth.requestDevice({filters: [{ services: [serviceUuid] }]})
  .then(device => {
    console.log('Verbindung mit dem GATT-Server.');
    return device.gatt.connect();
  })
  .then(server => {
    console.log('Suche den Sensor-Dienst.');
    return server.getPrimaryService(serviceUuid);
  })
  .then(service => {
    console.log('Suche die Temperatur-Charakteristik.');
    return service.getCharacteristic(characteristicUuid);
  })
  .then(characteristic => {
    myCharacteristic = characteristic;
    return myCharacteristic.startNotifications().then(_ => {
      console.log('Notifikationen werden empfangen.');
      myCharacteristic.addEventListener('characteristicvaluechanged',
          handleNotifications);
    });
  })
  .catch(error => { console.log(error); });
}

function onStopButtonClick() {
  if (myCharacteristic) {
    myCharacteristic.stopNotifications()
    .then(_ => {
      console.log('Notifikationen werden ignoriert.');
      myCharacteristic.removeEventListener('characteristicvaluechanged',
          handleNotifications);
    })
    .catch(error => { console.log(error); });
  }
}

function handleNotifications(event) {
  let value = event.target.value;
  const t = value.getInt16(0, true) / 100.0;
  console.log(t);
  document.querySelector('#temperature').innerHTML = t + '&#x00b0;C';
}

document.querySelector('#btn_start').addEventListener('click', onStartButtonClick);
document.querySelector('#btn_stop').addEventListener('click', onStopButtonClick);
