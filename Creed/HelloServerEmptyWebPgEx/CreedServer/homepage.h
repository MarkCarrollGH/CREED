String homePagePart1 = F(R"=====(<!DOCTYPE html>
<html lang="en" >
<head>
<!-- UTF-8 character set covers most characters in the world -->
  <meta charset="utf-8">
  <!-- Make page respond to screen size !-->
  <meta name="viewport" content="width=device-width, initial-scale=1, viewport-fit=cover">
  <link rel="stylesheet" href="https://fonts.googleapis.com/css?family=Open+Sans:400,700&display=swap">

<title> Creed Card Reading </title>
<style>
   
	  body{       
      background-color: #808080;
      margin: 0 auto;
		  font-family: 'Open Sans', sans-serif;
	  }
    
	   #flex-Container{
      display: flex;
      flex-direction: column;
      background-color: #808080;
      align-items: center;
     }
      
    #button{
    	display: flex;
    	flex-direction: column;
    	align-items: center;
    }
    
    #textToRead{
    	display: flex;
    	flex-direction: column;
    	align-items: center;
    }
    
    h1{
    	font: bold;
    	font-size: 40px;
    	font-family: Arial;
    	color: #ffffff;
    	text-align: center;
    }
    
    p{
    	font-size: 25px;
    	font-family: Arial;
    	color: #ffffff;
    	text-align: center;
    }
    
    .top-bar {
      background-color: #333;
      color: #fff;
      padding: 10px;
      text-align: center;
      justify-content: center;
      margin-left: 5%;
      margin-right: 5%;
      margin-top: 2%;
    }
    .speaker-button {
      background-color: #4CAF50;
      border: none;
      color: white;
      padding: 15px 32px;
      text-align: center;
      text-decoration: none;
      display: inline-block;
      font-size: 16px;
      margin: 4px 2px;
      cursor: pointer;
      border-radius: 4px;
    }

    .speaker-icon {
      display: inline-block;
      vertical-align: middle;
      width: 20px;
      height: 20px;
      background-image: url('data:image/svg+xml;utf8,<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"><path d="M18 9l-6-6-6 6"></path><circle cx="12" cy="15" r="3"></circle></svg>');
      background-repeat: no-repeat;
      background-position: center;
      margin-right: 5px;
    }
    
</style>
</head>
	<body>
      <div class="top-bar">
            <h1>Creed</h1>
      </div>
      
      <div id="flex-Container">
        <p>Welcome to my website to display card text</p>
        <p>This website will display and read text for playing cards</p>

        <textarea id="textToRead" rows="4" cols="30">)=====");

String homePagePart2 = F(R"=====(
  </textarea>
        <br>
        <button class="speaker-button" onclick="speakText()">
          <span class="speaker-icon"></span>
          Speak
        </button>

      </div>

      <script>
          function speakText() {
              var textToRead = document.getElementById("textToRead").value;

              if ('speechSynthesis' in window) {
                var synthesis = window.speechSynthesis;
                var utterance = new SpeechSynthesisUtterance(textToRead);

                synthesis.speak(utterance);
              } 
              else {
                  alert('Your browser does not support the Web Speech API.');
              }
          }
      </script>
	</body>
</html>

)=====");
