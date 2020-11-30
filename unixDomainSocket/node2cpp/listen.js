const net = require('net');
const fs =  require('fs');
const SOCKET_FILE = "unix_socket";

const server = net.createServer((connection) => {
	console.log('connected.');
	connection.on('close', () => {
		console.log('disconnected.');
	});
	connection.on('data', (data) => {
		const obj = JSON.parse(data.toString())
		console.log(obj.good);
		connection.write('ok');
	});
	connection.on('error', (err) => {
		console.error(err.message);
	});
});
try {
	fs.unlinkSync(SOCKET_FILE);
} catch (error) {}
server.listen(SOCKET_FILE);
