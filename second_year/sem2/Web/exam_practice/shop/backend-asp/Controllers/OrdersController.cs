using backend_asp.Models;
using backend_asp.Models.DTOs;
using Microsoft.AspNetCore.Mvc;

namespace backend_asp.Controllers
{
    [ApiController]
    [Route("[controller]")]
    public class OrdersController : Controller
    {
        public ShopDbContext _db = new ShopDbContext();
        public OrdersController(ShopDbContext db) => _db = db;

        [HttpPost]
        public async Task<IActionResult> ConfirmOrder([FromBody] ConfirmOrderDTO request)
        {
            var basePrice = ComputeBasePrice(request);
            var totalPrice = basePrice + basePrice * GetFirstDiscount(request) + basePrice * GetSecondDiscount(request);

            var newOrder = new Order { UserId = request.UserId, TotalPrice = totalPrice };
            await _db.AddAsync(newOrder);
            await _db.SaveChangesAsync();

            int orderId = newOrder.Id;

            foreach (var product in request.Products)
            {
                var orderItem = new OrderItem { OrderId = orderId, ProductId = product.Id };
                await _db.AddAsync(orderItem);
            }

            await _db.SaveChangesAsync();

            return Ok(new
            {
                TotalPrice = totalPrice
            });
        }

        private decimal GetFirstDiscount(ConfirmOrderDTO request)
        {
            if (request.Products.Count > 2)
                return 0.1M;

            return 0;
        }

        private decimal GetSecondDiscount(ConfirmOrderDTO request)
        {
            Dictionary<String, int> categoryCount = new();

            foreach (var product in request.Products)
                if(product.Name != null)
                {
                    String category = product.Name.Substring(0, product.Name.IndexOf('-')).Trim().ToUpper();
                    if (categoryCount.ContainsKey(category))
                        ++categoryCount[category];
                    else
                        categoryCount[category] = 1;
                }

            foreach (var c in categoryCount)
                if (c.Value > 1) return 0.05M;

            return 0;
        }

        private decimal ComputeBasePrice(ConfirmOrderDTO request)
        {
            decimal basePrice = 0;

            foreach (var product in request.Products)
                basePrice += product.Price;

            return basePrice;
        }
    }
}
