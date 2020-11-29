const net = require('net');
const client = net.createConnection('/tmp/unix.sock');

client.on('connect', () => {
	console.log('connected.');
});
client.on('data', (data) => {
	console.log(data.toString());
});
client.on('end', () => {
	console.log('disconnected.');
});
client.on('error', (err) => {
	console.error(err.message);
});
const dict = {"hello": 1, "good": 2, "bye": 3};
client.write(JSON.stringify(dict));
