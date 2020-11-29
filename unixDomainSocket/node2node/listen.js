const net = require('net');
const fs =  require('fs');
const SOCKET_FILE = "unix_socket";

const server = net.createServer((connection) => {
	console.log('connected.');
	connection.on('close', () => {
		console.log('disconnected.');
	});
	connection.on('data', (data) => {
		console.log(data.toString());
	});
	connection.on('error', (err) => {
		console.error(err.message);
	});
	connection.write('unix domain socket');
	connection.end();
});
try {
	fs.unlinkSync(SOCKET_FILE);
} catch (error) {}
server.listen(SOCKET_FILE);
