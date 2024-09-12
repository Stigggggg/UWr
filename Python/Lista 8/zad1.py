import asyncio
import aiohttp
import json
from prywatne import api_key

#wersja bez klucza
url="https://api.chucknorris.io/jokes/random"

async def main():
    async with aiohttp.ClientSession() as session:
        async with session.get(url) as result:
            assert result.status==200
            res=await result.text()
        data=json.loads(res)
    return data["value"]

asyncio.set_event_loop_policy(asyncio.WindowsSelectorEventLoopPolicy())
print(asyncio.run(main()))

#wersja z kluczem
url2="https://api.nasa.gov/mars-photos/api/v1/rovers/curiosity/photos"

async def main2():
    query_params={"api_key": api_key,"earth_date":"2023-07-01"}
    async with aiohttp.ClientSession() as session:
        async with session.get(url2,params=query_params) as response:
            assert response.status==200
            photos_data=await response.json()
        photos=photos_data["photos"]
        print(photos[34]["img_src"])
        print(photos[0]["sol"])

asyncio.run(main2())






