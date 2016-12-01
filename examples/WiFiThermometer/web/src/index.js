import "./index.less";

function updateIndoor()
{
    ajax(
        "/api/data",
        res => {
            $(".indoor-temperature .degree", res.temperature);
            $(".indoor-temperature .unit", "摄氏度");

            let feeling = "体感舒适";
            if (res.temperature >= 28)
            {
                feeling = "体感较热";
            }
            else if (res.temperature <= 18)
            {
                feeling = "体感较冷";
            }
            $(".indoor-temperature .feeling", feeling);
        },
        () => {
            $(".indoor-temperature .degree", "!");
            $(".indoor-temperature .unit", "");
            $(".indoor-temperature .feeling", "错误");
        }
    );
}

function updateOutdoor()
{
    ajax(
        "http://api.jirengu.com/weather.php",
        res => {
            if (res.status === "success")
            {
                $("footer .location", res.results[0].currentCity);
                $("footer .desc", res.results[0].weather_data[0].weather + "，" + res.results[0].weather_data[0].wind);
                $("footer .temperature", res.results[0].weather_data[0].temperature);
            }
            else
            {
                $("footer", "天气预报服务当前无法使用。");
            }
        },
        () => {
            $("footer", "无法获得室外天气，请检查当前网路连接。");
        }
    );
}

function $(selector, text)
{
    if (text === undefined)
    {
        return document.querySelector(selector);
    }
    else
    {
        const element = document.querySelector(selector);
        element.innerText = text;
    }
}

function ajax(url, callback, errorCallback)
{
    const req = new XMLHttpRequest();
    req.onreadystatechange = function() {
        if (this.readyState == 4)
        {
            if (this.status == 200)
            {
                const result = JSON.parse(this.responseText);
                if (typeof(callback) === "function")
                {
                    callback(result);
                }
            }
            else
            {
                if (typeof(errorCallback) === "function")
                {
                    errorCallback();
                }
            }
        }
    };
    req.open("GET", url, true);
    req.send();
}

updateOutdoor();
updateIndoor();
setInterval(updateIndoor, 30 * 1000);
