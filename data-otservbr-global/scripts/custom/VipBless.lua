local VipUseBless = Action()

function VipUseBless.onUse(player, item, fromPosition, target, toPosition, isHotkey)
    print(blessings, "haghagag")

    local blessings = 0
    for i = 2, 8 do
        if player:hasBlessing(i) then
            blessings = blessings + 1
        end
    end
    if player:isVip() then
        if player:getStorageValue(35785) == -1 or player:getStorageValue(35785) < os.time() then
            if blessings < 7 then
                for i = 2, 8 do
                    player:addBlessing(i, 1)
                end
                player:sendTextMessage(MESSAGE_EVENT_ADVANCE, "Voc� recebeu todas as bless por ser vip, s� pode ser usado a cada 24h.")
                player:setStorageValue(35785, os.time() + (24 * 60 * 60))
                player:getPosition():sendMagicEffect(CONST_ME_HOLYAREA)
            else
                 player:sendTextMessage(MESSAGE_EVENT_ADVANCE, "Voc� j� tem todas as bless.")
            end
        else
             player:sendTextMessage(MESSAGE_EVENT_ADVANCE, "Ainda n�o deu as 24horas des da sua ultima bless Free-VIP.")
        end
    else
         player:sendTextMessage(MESSAGE_EVENT_ADVANCE, "Voc� n�o � VIP para pegar sua bless full di�ria!")
    end
	return true
end

VipUseBless:aid(28139)
VipUseBless:register()
