const express = require('express');
const app = express();
const port = 80;

app.use(express.json());

let data = [];

app.post('/', (req, res) => {
    data.push(req.body);
    res.send('Data received');
});

app.get('/data', (req, res) => {
    res.json(data);
});

app.listen(port, () => {
    console.log(`Server listening at http://localhost:${port}`);
});