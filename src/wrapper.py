from http.server import SimpleHTTPRequestHandler, HTTPServer

import subprocess

class SimplePostHandler(SimpleHTTPRequestHandler):
    chess_game = None
    win = False
    def do_POST(self):
        # Get the content length from the request headers
        content_length = int(self.headers['Content-Length'])
        response = ""
        
        # Read the POST data
        post_data = self.rfile.read(content_length).decode('utf-8')

        proc.stdin.write(post_data + "\n")
        proc.stdin.flush()
        
        while True:
                # Read one line of output from the subprocess
            line = proc.stdout.readline()
            response += line
            if line == "Your Turn: \n":
                # No more output, or the process has finished
                break
    
            if "valid move" in line:
                break
    
            if "Wins" in line:
                self.win = True
                break

        # Send a response
        self.send_response(200)
        self.send_header('Content-type', 'text/html')
        self.end_headers()

        # Construct a response message

        # Send the response back to the client
        self.wfile.write(response.encode('utf-8'))



if __name__ == '__main__':

    command = ["./Chess.exe", "1", "4", "1", "0"]

    proc = subprocess.Popen(command, stdin=subprocess.PIPE, stdout=subprocess.PIPE, universal_newlines=True)

    SimplePostHandler.chess_game = proc

    # Set the port number
    port = 8080

    # Create the server with the custom handler
    server = HTTPServer(('localhost', port), SimplePostHandler)

    print(f'Starting server on port {port}')

    # Run the server
    server.serve_forever()
