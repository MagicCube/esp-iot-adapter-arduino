import "./index.less";

function updateIndoor()
{
    const $indoor = $(".indoor-temperature");
    $.ajax({
        dataType: "json",
        url: "/api/data",
    }).then(res => {
        $indoor.find(".degree").text(res.temperature);
        $indoor.find(".unit").text("摄氏度");

        let feeling = "体感舒适";
        if (res.temperature >= 28)
        {
            feeling = "体感较热";
        }
        else if (res.temperature <= 18)
        {
            feeling = "体感较冷";
        }
        $indoor.find(".feeling").text(feeling);
    }).catch(e => {
        $indoor.find(".degree").text("!");
        $indoor.find(".unit").text("");
        $indoor.find(".feeling").text("错误");
    });
}

function updateOutdoor()
{
    const $footer = $("footer");
    $.ajax({
        dataType: "json",
        url: "http://api.jirengu.com/weather.php",
    }).then(res => {
        if (res.status === "success")
        {
            $footer.find(".location").text(res.results[0].currentCity);
            $footer.find(".desc").text(res.results[0].weather_data[0].weather + "，" + res.results[0].weather_data[0].wind);
            $footer.find(".temperature").text(res.results[0].weather_data[0].temperature);
        }
        else
        {
            $footer.text("天气预报服务当前无法使用。");
        }
    }).catch(e => {
        $footer.text("无法获得室外天气，请检查当前网路连接。");
    });
}

$(() => {
    updateOutdoor();
    updateIndoor();
    setInterval(updateIndoor, 30 * 1000);
});
