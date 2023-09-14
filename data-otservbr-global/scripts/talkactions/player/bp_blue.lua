local bp = TalkAction("!bp blue")

function bp.onSay(player, words, param)
    if player:removeMoneyBank(10) then
        player:getPosition():sendMagicEffect(CONST_ME_MAGIC_BLUE)
        player:addItem(2869, 1)
        player:sendTextMessage(MESSAGE_EVENT_ADVANCE, "You have bought a blue backpack!")
    else
        player:getPosition():sendMagicEffect(CONST_ME_POFF)
        player:sendCancelMessage("You do not have enough money.")
    end
end

bp:register()