# The client sends the complete path to a file. The server returns back the length of the file 
# and its content in the case the file exists. When the file does not exist the server returns 
# a length of -1 and no content.The client will store the content in a file with the same name 
# as the input file with the suffix –copy appended (ex: for f.txt => f.txt-copy).

import asyncio
import socket 
import os
import struct
import sys

CHUNK = 64 * 1024 # 64KB
PORT = 5000
HOST = '0.0.0.0'


async def handle_client(reader: asyncio.StreamReader, writer: asyncio.StreamWriter):
    addr = writer.get_extra_info("peername")
    print(f"Client connected: {addr}")

    try:
        # Read the path until EOF or newline
        data = await reader.readuntil(b"\n") if not reader.at_eof() else await reader.read()
        if not data:
            writer.close()
            await writer.wait_closed()
            return

        # Remove trailing newline/spaces
        path = data.decode().strip()
        print(f"Requested path: {path}")

        # Check if file exists
        if not os.path.isfile(path):
            print("File not found.")
            writer.write(struct.pack("!q", -1))
            await writer.drain()
            writer.close()
            await writer.wait_closed()
            return

        # Send file length
        file_len = os.path.getsize(path)
        writer.write(struct.pack("!q", file_len))
        await writer.drain()

        # Send file content
        with open(path, "rb") as f:
            while True:
                chunk = f.read(CHUNK)
                if not chunk:
                    break
                writer.write(chunk)
                await writer.drain()

        print(f"Sent file '{path}' ({file_len} bytes) to {addr}")

    except asyncio.IncompleteReadError:
        print(f"Client {addr} disconnected early.")
    except Exception as e:
        print(f"Error: {e}")
    finally:
        writer.close()
        await writer.wait_closed()
        print(f"Connection with {addr} closed.")


    peer = writer.get_extra_info('peername')
    try: 
        raw = await reader.readexactly(4)
        (path_len,) = struct.unpack('!I', raw)
        if path_len > 4096 or path_len == 0:
            writer.write(struct.pack('!q', -1))
            await writer.drain()
            writer.close()
            await writer.wait_closed()
            return
        
        path_bytes = await reader.readexactly(path_len)
        path = path_bytes.decode('utf-8', errors='strict')

        try: 
            st = await asyncio.get_running_loop().run_in_executor(None, os.stat, path)
            if not os.path.isfile(path):
                raise FileNotFoundError
            file_size = st.st_size
        except Exception:
            writer.write(struct.pack('!q', -1))
            await writer.drain()
            writer.close()
            await writer.wait_closed()
            return
        
        writer.write(struct.pack('!q', file_size))
        await writer.drain()

        def _read_chunks(p):
            with open(p, 'rb') as f:
                while True:
                    chunk = f.read(CHUNK)
                    if not chunk:
                        break
                    yield chunk

        loop = asyncio.get_running_loop()

        for chunk in await loop.run_in_executor(None, lambda: list(_read_chunks(path))):
            writer.write(chunk)
            await writer.drain()

    except asyncio.IncompleteReadError:
        pass
    except Exception:
        pass

    finally:
        try:
            writer.close()
            await writer.wait_closed()
        except Exception:
            pass

async def main():
    port = int(sys.argv[1]) if len(sys.argv) > 1 else PORT
    server = await asyncio.start_server(handle_client, HOST, port, backlog=64)
    print(f"Python server listening on port {port}")
    async with server:
        await server.serve_forever()

if __name__ == "__main__":
    asyncio.run(main())