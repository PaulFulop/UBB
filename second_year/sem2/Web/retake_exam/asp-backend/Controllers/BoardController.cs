using asp_backend.Models;
using asp_backend.Models.DTOs;
using Microsoft.AspNetCore.Components.Web.Virtualization;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;

namespace asp_backend.Controllers
{
    [ApiController]
    [Route("[controller]")]
    public class BoardController : Controller
    {
        private RetakeDbContext _db = new RetakeDbContext();
        public BoardController(RetakeDbContext db) => _db = db;

        [HttpGet("items")]
        public async Task<IActionResult> GetAllItems()
        {
            var itemsResponse = new List<ItemResponse>();
            var items = await _db.Items.ToListAsync();

            foreach (var item in items)
            {
                var seller = _db.Users.FirstOrDefault(u => u.Id == item.UserId).Username;
                var numOfBids = _db.Bids.Where(b => b.ItemId == item.Id).Count();

                itemsResponse.Add(new ItemResponse
                {
                    Id = item.Id,
                    Title = item.Title,
                    Seller = seller,
                    CurrentPrice = item.CurrentPrice,
                    NumOfBids = numOfBids
                });
            }

            return Ok(itemsResponse);
        }

        [HttpPost("items/{userId}")]
        public async Task<IActionResult> AddItem(int userId, [FromBody]ItemRequest request)
        {
            await _db.Items.AddAsync(new Item
            {
                UserId = userId,
                Title = request.Title,
                Description = request.Description,
                StartingPrice = request.StartingPrice,
                CurrentPrice = request.StartingPrice
            });

            await _db.SaveChangesAsync();
            return Ok();
        }

        [HttpDelete("items/{userId}/{itemId}")]
        public async Task<IActionResult> DeleteItem(int userId, int itemId)
        {
            var item = await _db.Items.FirstOrDefaultAsync(i => i.Id == itemId);
            if (item == null) return NotFound("Item not found");
            if (item.UserId != userId) return BadRequest("This item does not belong to you!");

            _db.Items.Remove(item);
            await _db.SaveChangesAsync();
            return Ok("Item deleted!");
        }

        [HttpGet("items/history/{itemId}")]
        public async Task<IActionResult> GetItemHistory(int itemId)
        {
            var bids = await _db.Bids.Where(b => b.ItemId == itemId).ToListAsync();
            var bidsResponse = new List<BidResponse>();

            foreach(var bid in bids)
            {
                string userName = _db.Users.FirstOrDefault(u => u.Id == bid.UserId).Username;
                string itemName = _db.Items.FirstOrDefault(i => i.Id == bid.ItemId).Title;

                bidsResponse.Add(new BidResponse
                {
                    Id = bid.Id,
                    UserName = userName,
                    ItemName = itemName,
                    Amount = bid.Amount,
                    PlacedAt = bid.PlacedAt,
                });
            }

            return Ok(bidsResponse);
        }

        [HttpPost("items/history/place/{userId}/{itemId}/{amount}")]
        public async Task<IActionResult> PlaceBid(int userId, int itemId, int amount)
        {
            var item = await _db.Items.FirstOrDefaultAsync(i => i.Id == itemId);

            if (item == null) return NotFound();
            if (item.UserId == userId) return BadRequest("This is your item!");
            if (amount <= item.CurrentPrice) return BadRequest("Not enough money");

            item.CurrentPrice = amount;
            await _db.Bids.AddAsync(new Bid { ItemId = itemId, UserId = userId, Amount = amount, PlacedAt = DateTime.Now});
            await _db.SaveChangesAsync();

            return Ok("Bid added");
        }
    }
}
