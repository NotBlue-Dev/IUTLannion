//http://127.0.0.1:5500/?month=May
document.addEventListener("DOMContentLoaded", function(event) {
    const urlParams = new URLSearchParams(window.location.search);
    
    let month = urlParams.get('month') ? urlParams.get('month') : new Date().toLocaleString('default', { month: 'long' });

    let year = new Date().getFullYear();
    createWeeks(month, year);
    
    let days = document.querySelectorAll(".calendar__day");

    days.forEach((day) => {
        day.addEventListener("click", () => {
            let date = day.children[0].innerHTML;
            let today = document.querySelector(".today");
            today.classList.remove("today");
            day.classList.add("today");
            let todayTask = document.querySelector(".calendar__task--today");
            todayTask.classList.remove("calendar__task--today");
            day.children[1].classList.add("calendar__task--today");
            let bar__days = document.querySelectorAll(".top-bar__days");

            let index = Array.prototype.indexOf.call(day.parentNode.children, day);
            document.querySelectorAll(".sidebar__heading")[0].innerHTML = bar__days[index].id + "<br>" + document.querySelectorAll(".title-bar__year")[0].innerText.split(" ")[2] + " " + date;
            
            let size = getAndDisplayTasks(day.children[0].id);
            if(size != 0) {
                day.children[1].innerHTML = size + " Items";
            }
        });
    });
});

function createWeeks(month, year) {

    let today = new Date().toLocaleString('default', { weekday: 'long' });
    let day = new Date().getDate();
    document.querySelectorAll(".sidebar__heading")[0].innerHTML = `${today}<br>${month} ${day}`;

    const daysInMonth = (year, month) => new Date(year, new Date(Date.parse(month +" 1, 2023")).getMonth()+1, 0).getDate();

    let currentDay = new Date().getDate();
    let res = daysInMonth(year, month);

    let count = 0;
    let inactive = false;

    document.querySelectorAll(".title-bar__year")[0].innerHTML = `Calendar > ${month} ${year}`

    let calendar = document.querySelector(".calendar__days");
    for(let i = 0; i < 5; i++) {
        let section = document.createElement("section");
        section.classList.add("calendar__week");
        for(let i = 0; i < 7; i++) {
            if(count > res) {
                count = 0; 
                inactive = true;
            }
            count++;

            let div = document.createElement("div");
            div.classList.add("calendar__day");
            if(count == currentDay) div.classList.add("today");
            if(inactive) div.classList.add("inactive");
            let span = document.createElement("span");
            span.classList.add("calendar__date");
            span.innerHTML = count;
            let span2 = document.createElement("span");
            span2.classList.add("calendar__task");
            if(count == currentDay) {
                span2.classList.add("calendar__task--today");
            }
            span.id = count + "/" + month;
            let size = JSON.parse(localStorage.getItem(span.id)) ;
            if(size != 0 && size != null) {
                getAndDisplayTasks(span.id);
                
                span2.innerHTML = size.length + " Items";
            }
            div.appendChild(span);
            div.appendChild(span2);
            section.appendChild(div);
        }
        calendar.appendChild(section);
    }
}