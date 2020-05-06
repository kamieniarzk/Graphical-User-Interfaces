using Calendar.ViewModels;
using Microsoft.AspNetCore.Mvc;
using System;

namespace Calendar.Controllers
{
    public class EventController : Controller
    {
        public IActionResult Index()
        {
            return View();
        }

        public IActionResult Delete(string Id)
        {
            EventViewModel model = new EventViewModel();
            string date = model.Get(Id).Date.ToString("yyyy'-'MM'-'dd");
            if(model.Remove(Id)) 
            {
                return Redirect("/Home/Day/?date=" + date);
            } else
            {
                return Redirect("/Shared/Error");
            }
        }
        [HttpGet]
        public IActionResult Add()
        {
            ViewBag.date = HomeController.CurrentDate;
            return View();
        }

        [HttpPost]
        [Route("/Event/Add/")]
        public IActionResult Added(string description, string time)
        {
            EventViewModel model = new EventViewModel();
            if (time != null)
            {
                time = HomeController.CurrentDate.ToString("yyyy-MM-dd") + 'T' + time;
                model.Add(new Models.Event() { Date = DateTime.Parse(time), Description = description });
            }
            else 
            {
                model.Add(new Models.Event() { Date = HomeController.CurrentDate, Description = description });
            }
            return Redirect("/Home/Day/?date=" + HomeController.CurrentDate.ToString("yyyy-MM-dd"));
        }

        [HttpGet]
        public IActionResult Edit(string Id)
        {
            EventViewModel model = new EventViewModel();
            ViewBag.date = HomeController.CurrentDate;
            ViewBag.Id = Id;
            return View(model);
        }

        [HttpPost]
        [Route("/Event/Edit/")]
        public IActionResult Edit(string description, string id, string time)
        {
            EventViewModel model = new EventViewModel();
            if (time != null)
            {
                time = HomeController.CurrentDate.ToString("yyyy-MM-dd") + 'T' + time;
                model.Edit(id, DateTime.Parse(time), description);
            }
            else
            {
                model.Edit(id, HomeController.CurrentDate, description);
            }
            ViewBag.date = HomeController.CurrentDate;
            return Redirect("/Home/Day/?date=" + HomeController.CurrentDate.ToString("yyyy-MM-dd"));
        }

    }
}