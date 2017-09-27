### Environment Setup ###

* Python version 3.5.2
* Install pip required packages `pip3 install -r requirements.txt --user`
* Setup Flask environment variables
  1. `export FLASK_APP=server.py flask run`
  2. `export FLASK_DEBUG=1`
* To run server `flask run`
  * If the error "No such file or directory" occurs use `python3 -m flask run`
* To bundle the js files in the static/src directory into static/js/bundle.js `browserify static/src/* -o static/js/bundle.js -t [ babelify --presets [ env ] ]`
  * Or you can use the npm script `npm run build`
* The npm script `npm run serve` will re-bundle the js file for you and start the flask server
