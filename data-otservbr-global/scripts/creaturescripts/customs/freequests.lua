local stage = configManager.getNumber(configKeys.FREE_QUEST_STAGE)

local questTable = {
	{ storage = Storage.BigfootBurden.QuestLine, storageValue = 2 },
	{ storage = Storage.BigfootBurden.QuestLine, storageValue = 4 },
	{ storage = Storage.BigfootBurden.QuestLine, storageValue = 7 },
	{ storage = Storage.BigfootBurden.QuestLine, storageValue = 9 },
	{ storage = Storage.BigfootBurden.QuestLine, storageValue = 12 },
	{ storage = Storage.BigfootBurden.Shooting, storageValue = 5 },
	{ storage = Storage.BigfootBurden.QuestLine, storageValue = 16 },
	{ storage = Storage.BigfootBurden.QuestLine, storageValue = 20 },
	{ storage = Storage.BigfootBurden.QuestLine, storageValue = 23 },
	{ storage = Storage.BigfootBurden.QuestLineComplete, storageValue = 2 },
	{ storage = Storage.BigfootBurden.Rank, storageValue = 1440 },
	{ storage = Storage.BigfootBurden.Warzone1Access, storageValue = 2 },
	{ storage = Storage.BigfootBurden.Warzone2Access, storageValue = 2 },
	{ storage = Storage.BigfootBurden.Warzone3Access, storageValue = 2 },
	{ storage = Storage.DangerousDepths.Questline, storageValue = 10 },
	{ storage = Storage.DangerousDepths.Access.LavaPumpWarzoneVI, storageValue = 10 },
	{ storage = Storage.DangerousDepths.Access.LavaPumpWarzoneV, storageValue = 10 },
	{ storage = Storage.DangerousDepths.Access.LavaPumpWarzoneIV, storageValue = 30 },
	{ storage = Storage.DangerousDepths.Dwarves.Status, storageValue = 10 },
	{ storage = Storage.DangerousDepths.Scouts.Status, storageValue = 10 },
	{ storage = Storage.DangerousDepths.Gnomes.Status, storageValue = 10 },
	{ storage = Storage.Quest.U8_4.InServiceOfYalahar.Questline, storageValue = 51 },
	{ storage = Storage.Quest.U8_4.InServiceOfYalahar.Mission01, storageValue = 6 },
	{ storage = Storage.Quest.U8_4.InServiceOfYalahar.Mission02, storageValue = 8 },
	{ storage = Storage.Quest.U8_4.InServiceOfYalahar.Mission03, storageValue = 6 },
	{ storage = Storage.Quest.U8_4.InServiceOfYalahar.Mission04, storageValue = 6 },
	{ storage = Storage.Quest.U8_4.InServiceOfYalahar.Mission05, storageValue = 8 },
	{ storage = Storage.Quest.U8_4.InServiceOfYalahar.Mission06, storageValue = 5 },
	{ storage = Storage.Quest.U8_4.InServiceOfYalahar.Mission07, storageValue = 5 },
	{ storage = Storage.Quest.U8_4.InServiceOfYalahar.Mission08, storageValue = 4 },
	{ storage = Storage.Quest.U8_4.InServiceOfYalahar.Mission09, storageValue = 2 },
	{ storage = Storage.Quest.U8_4.InServiceOfYalahar.Mission10, storageValue = 1 },
	{ storage = Storage.Quest.U8_4.InServiceOfYalahar.SewerPipe01, storageValue = 1 },
	{ storage = Storage.Quest.U8_4.InServiceOfYalahar.SewerPipe02, storageValue = 1 },
	{ storage = Storage.Quest.U8_4.InServiceOfYalahar.SewerPipe03, storageValue = 1 },
	{ storage = Storage.Quest.U8_4.InServiceOfYalahar.SewerPipe04, storageValue = 1 },
	{ storage = Storage.Quest.U8_4.InServiceOfYalahar.DiseasedDan, storageValue = 1 },
	{ storage = Storage.Quest.U8_4.InServiceOfYalahar.DiseasedBill, storageValue = 1 },
	{ storage = Storage.Quest.U8_4.InServiceOfYalahar.DiseasedFred, storageValue = 1 },
	{ storage = Storage.Quest.U8_4.InServiceOfYalahar.AlchemistFormula, storageValue = 1 },
	{ storage = Storage.Quest.U8_4.InServiceOfYalahar.BadSide, storageValue = 1 },
	{ storage = Storage.Quest.U8_4.InServiceOfYalahar.GoodSide, storageValue = 1 },
	{ storage = Storage.Quest.U8_4.InServiceOfYalahar.MrWestDoor, storageValue = 1 },
	{ storage = Storage.Quest.U8_4.InServiceOfYalahar.MrWestStatus, storageValue = 1 },
	{ storage = Storage.Quest.U8_4.InServiceOfYalahar.TamerinStatus, storageValue = 1 },
	{ storage = Storage.Quest.U8_4.InServiceOfYalahar.MorikSummon, storageValue = 1 },
	{ storage = Storage.Quest.U8_4.InServiceOfYalahar.QuaraState, storageValue = 1 },
	{ storage = Storage.Quest.U8_4.InServiceOfYalahar.QuaraSplasher, storageValue = 1 },
	{ storage = Storage.Quest.U8_4.InServiceOfYalahar.QuaraSharptooth, storageValue = 1 },
	{ storage = Storage.Quest.U8_4.InServiceOfYalahar.QuaraInky, storageValue = 1 },
	{ storage = Storage.Quest.U8_4.InServiceOfYalahar.MatrixState, storageValue = 1 },
	{ storage = Storage.Quest.U8_4.InServiceOfYalahar.NotesPalimuth, storageValue = 1 },
	{ storage = Storage.Quest.U8_4.InServiceOfYalahar.NotesAzerus, storageValue = 1 },
	{ storage = Storage.Quest.U8_4.InServiceOfYalahar.DoorToAzerus, storageValue = 1 },
	{ storage = Storage.Quest.U8_4.InServiceOfYalahar.DoorToBog, storageValue = 1 },
	{ storage = Storage.Quest.U8_4.InServiceOfYalahar.DoorToLastFight, storageValue = 1 },
	{ storage = Storage.Quest.U8_4.InServiceOfYalahar.DoorToMatrix, storageValue = 1 },
	{ storage = Storage.Quest.U8_4.InServiceOfYalahar.DoorToQuara, storageValue = 1 },
	{ storage = Storage.CultsOfTibia.Questline, storageValue = 7 },
	{ storage = Storage.CultsOfTibia.Minotaurs.JamesfrancisTask, storageValue = 1 },
	{ storage = Storage.CultsOfTibia.Minotaurs.Mission, storageValue = 1 },
	{ storage = Storage.CultsOfTibia.Minotaurs.BossTimer, storageValue = 1 },
	{ storage = Storage.CultsOfTibia.MotA.Mission, storageValue = 1 },
	{ storage = Storage.CultsOfTibia.MotA.Stone1, storageValue = 1 },
	{ storage = Storage.CultsOfTibia.MotA.Stone2, storageValue = 1 },
	{ storage = Storage.CultsOfTibia.MotA.Stone3, storageValue = 1 },
	{ storage = Storage.CultsOfTibia.MotA.Answer, storageValue = 1 },
	{ storage = Storage.CultsOfTibia.MotA.QuestionId, storageValue = 1 },
	{ storage = Storage.CultsOfTibia.Barkless.Mission, storageValue = 1 },
	{ storage = Storage.CultsOfTibia.Barkless.sulphur, storageValue = 4 },
	{ storage = Storage.CultsOfTibia.Barkless.Tar, storageValue = 3 },
	{ storage = Storage.CultsOfTibia.Barkless.Ice, storageValue = 3 },
	{ storage = Storage.CultsOfTibia.Barkless.Objects, storageValue = 1 },
	{ storage = Storage.CultsOfTibia.Barkless.Temp, storageValue = 1 },
	{ storage = Storage.CultsOfTibia.Orcs.Mission, storageValue = 1 },
	{ storage = Storage.CultsOfTibia.Orcs.LookType, storageValue = 1 },
	{ storage = Storage.CultsOfTibia.Orcs.BossTimer, storageValue = 1 },
	{ storage = Storage.CultsOfTibia.Life.Mission, storageValue = 7 },
	{ storage = Storage.CultsOfTibia.Life.BossTimer, storageValue = 1 },
	{ storage = Storage.CultsOfTibia.Humans.Mission, storageValue = 1 },
	{ storage = Storage.CultsOfTibia.Humans.Vaporized, storageValue = 1 },
	{ storage = Storage.CultsOfTibia.Humans.Decaying, storageValue = 1 },
	{ storage = Storage.CultsOfTibia.Humans.BossTimer, storageValue = 1 },
	{ storage = Storage.CultsOfTibia.Misguided.Mission, storageValue = 1 },
	{ storage = Storage.CultsOfTibia.Misguided.Monsters, storageValue = 1 },
	{ storage = Storage.CultsOfTibia.Misguided.Exorcisms, storageValue = 1 },
	{ storage = Storage.CultsOfTibia.Misguided.Time, storageValue = 1 },
	{ storage = Storage.CultsOfTibia.Misguided.BossTimer, storageValue = 1 },
	{ storage = Storage.CultsOfTibia.Minotaurs.EntranceAccessDoor, storageValue = 1 },
	{ storage = Storage.CultsOfTibia.Minotaurs.AccessDoor, storageValue = 1 },
	{ storage = Storage.Quest.U7_6.ExplorerSociety.QuestLine, storageValue = 1 },
	{ storage = Storage.Quest.U7_6.ExplorerSociety.QuestLine, storageValue = 4 },
	{ storage = Storage.Quest.U7_6.ExplorerSociety.QuestLine, storageValue = 7 },
	{ storage = Storage.Quest.U7_6.ExplorerSociety.QuestLine, storageValue = 16 },
	{ storage = Storage.Quest.U7_6.ExplorerSociety.QuestLine, storageValue = 26 },
	{ storage = Storage.Quest.U7_6.ExplorerSociety.QuestLine, storageValue = 29 },
	{ storage = Storage.Quest.U7_6.ExplorerSociety.QuestLine, storageValue = 32 },
	{ storage = Storage.Quest.U7_6.ExplorerSociety.QuestLine, storageValue = 35 },
	{ storage = Storage.Quest.U7_6.ExplorerSociety.QuestLine, storageValue = 38 },
	{ storage = Storage.Quest.U7_6.ExplorerSociety.QuestLine, storageValue = 41 },
	{ storage = Storage.Quest.U7_6.ExplorerSociety.QuestLine, storageValue = 43 },
	{ storage = Storage.Quest.U7_6.ExplorerSociety.QuestLine, storageValue = 46 },
	{ storage = Storage.Quest.U7_6.ExplorerSociety.QuestLine, storageValue = 47 },
	{ storage = Storage.Quest.U7_6.ExplorerSociety.QuestLine, storageValue = 50 },
	{ storage = Storage.Quest.U7_6.ExplorerSociety.QuestLine, storageValue = 55 },
	{ storage = Storage.Quest.U7_6.ExplorerSociety.QuestLine, storageValue = 56 },
	{ storage = Storage.Quest.U7_6.ExplorerSociety.QuestLine, storageValue = 58 },
	{ storage = Storage.Quest.U7_6.ExplorerSociety.QuestLine, storageValue = 61 },
	{ storage = Storage.Quest.U7_6.ExplorerSociety.CalassaQuest, storageValue = 2 },
	{ storage = Storage.ForgottenKnowledge.Tomes, storageValue = 1 },
	{ storage = Storage.ForgottenKnowledge.LastLoreKilled, storageValue = 1 },
	{ storage = Storage.ForgottenKnowledge.TimeGuardianKilled, storageValue = 1 },
	{ storage = Storage.ForgottenKnowledge.HorrorKilled, storageValue = 1 },
	{ storage = Storage.ForgottenKnowledge.DragonkingKilled, storageValue = 1 },
	{ storage = Storage.ForgottenKnowledge.ThornKnightKilled, storageValue = 1 },
	{ storage = Storage.ForgottenKnowledge.LloydKilled, storageValue = 1 },
	{ storage = Storage.ForgottenKnowledge.LadyTenebrisKilled, storageValue = 1 },
	{ storage = Storage.ForgottenKnowledge.AccessMachine, storageValue = 1 },
	{ storage = Storage.ForgottenKnowledge.AccessLavaTeleport, storageValue = 1 },
	{ storage = Storage.Quest.U8_0.BarbarianTest.Questline, storageValue = 8 },
	{ storage = Storage.Quest.U8_0.BarbarianTest.Mission01, storageValue = 3 },
	{ storage = Storage.Quest.U8_0.BarbarianTest.Mission02, storageValue = 3 },
	{ storage = Storage.Quest.U8_0.BarbarianTest.Mission03, storageValue = 3 },
	{ storage = Storage.ChildrenoftheRevolution.Questline, storageValue = 21 },
	{ storage = Storage.ChildrenoftheRevolution.Mission00, storageValue = 2 },
	{ storage = Storage.ChildrenoftheRevolution.Mission01, storageValue = 3 },
	{ storage = Storage.ChildrenoftheRevolution.Mission02, storageValue = 5 },
	{ storage = Storage.ChildrenoftheRevolution.Mission03, storageValue = 3 },
	{ storage = Storage.ChildrenoftheRevolution.Mission04, storageValue = 6 },
	{ storage = Storage.ChildrenoftheRevolution.Mission05, storageValue = 3 },
	{ storage = Storage.ChildrenoftheRevolution.SpyBuilding01, storageValue = 1 },
	{ storage = Storage.ChildrenoftheRevolution.SpyBuilding02, storageValue = 1 },
	{ storage = Storage.ChildrenoftheRevolution.SpyBuilding03, storageValue = 1 },
	{ storage = Storage.ChildrenoftheRevolution.StrangeSymbols, storageValue = 1 },
	{ storage = Storage.Quest.U7_4.DjinnWar.Faction.Greeting, storageValue = 2 },
	{ storage = Storage.Quest.U7_4.DjinnWar.Faction.MaridDoor, storageValue = 2 },
	{ storage = Storage.Quest.U7_4.DjinnWar.Faction.EfreetDoor, storageValue = 2 },
	{ storage = Storage.Quest.U7_4.DjinnWar.EfreetFaction.Start, storageValue = 1 },
	{ storage = Storage.Quest.U7_4.DjinnWar.EfreetFaction.Mission01, storageValue = 3 },
	{ storage = Storage.Quest.U7_4.DjinnWar.EfreetFaction.Mission02, storageValue = 3 },
	{ storage = Storage.Quest.U7_4.DjinnWar.EfreetFaction.Mission03, storageValue = 3 },
	{ storage = Storage.Quest.U7_4.DjinnWar.MaridFaction.Start, storageValue = 1 },
	{ storage = Storage.Quest.U7_4.DjinnWar.MaridFaction.Mission01, storageValue = 2 },
	{ storage = Storage.Quest.U7_4.DjinnWar.MaridFaction.Mission02, storageValue = 2 },
	{ storage = Storage.Quest.U7_4.DjinnWar.MaridFaction.RataMari, storageValue = 2 },
	{ storage = Storage.Quest.U7_4.DjinnWar.MaridFaction.Mission03, storageValue = 3 },
	{ storage = Storage.Quest.U8_4.InServiceOfYalahar.TheWayToYalahar, storageValue = 1 },
	{ storage = Storage.Quest.U8_4.InServiceOfYalahar.SearoutesAroundYalahar.TownsCounter, storageValue = 5 },
	{ storage = Storage.Quest.U8_4.InServiceOfYalahar.SearoutesAroundYalahar.AbDendriel, storageValue = 1 },
	{ storage = Storage.Quest.U8_4.InServiceOfYalahar.SearoutesAroundYalahar.Darashia, storageValue = 1 },
	{ storage = Storage.Quest.U8_4.InServiceOfYalahar.SearoutesAroundYalahar.Venore, storageValue = 1 },
	{ storage = Storage.Quest.U8_4.InServiceOfYalahar.SearoutesAroundYalahar.Ankrahmun, storageValue = 1 },
	{ storage = Storage.Quest.U8_4.InServiceOfYalahar.SearoutesAroundYalahar.PortHope, storageValue = 1 },
	{ storage = Storage.Quest.U8_4.InServiceOfYalahar.SearoutesAroundYalahar.Thais, storageValue = 1 },
	{ storage = Storage.Quest.U8_4.InServiceOfYalahar.SearoutesAroundYalahar.LibertyBay, storageValue = 1 },
	{ storage = Storage.Quest.U8_4.InServiceOfYalahar.SearoutesAroundYalahar.Carlin, storageValue = 1 },
	{ storage = Storage.Quest.U8_4.TheHiddenCityOfBeregar.DefaultStart, storageValue = 1 },
	{ storage = Storage.Quest.U8_4.TheHiddenCityOfBeregar.GoingDown, storageValue = 1 },
	{ storage = Storage.Quest.U8_4.TheHiddenCityOfBeregar.WayToBeregar, storageValue = 1 },
	{ storage = Storage.Quest.U8_0.TheIceIslands.Questline, storageValue = 40 },
	{ storage = Storage.Quest.U8_0.TheIceIslands.Mission01, storageValue = 3 },
	{ storage = Storage.Quest.U8_0.TheIceIslands.Mission02, storageValue = 5 },
	{ storage = Storage.Quest.U8_0.TheIceIslands.Mission03, storageValue = 3 },
	{ storage = Storage.Quest.U8_0.TheIceIslands.Mission04, storageValue = 2 },
	{ storage = Storage.Quest.U8_0.TheIceIslands.Mission05, storageValue = 6 },
	{ storage = Storage.Quest.U8_0.TheIceIslands.Mission06, storageValue = 8 },
	{ storage = Storage.Quest.U8_0.TheIceIslands.Mission07, storageValue = 3 },
	{ storage = Storage.Quest.U8_0.TheIceIslands.Mission08, storageValue = 4 },
	{ storage = Storage.Quest.U8_0.TheIceIslands.Mission09, storageValue = 2 },
	{ storage = Storage.Quest.U8_0.TheIceIslands.Mission10, storageValue = 2 },
	{ storage = Storage.Quest.U8_0.TheIceIslands.Mission11, storageValue = 2 },
	{ storage = Storage.Quest.U8_0.TheIceIslands.Mission12, storageValue = 6 },
	{ storage = Storage.Quest.U8_0.TheIceIslands.yakchalDoor, storageValue = 1 },
	{ storage = Storage.Quest.U8_2.TheInquisitionQuest.Questline, storageValue = 25 },
	{ storage = Storage.Quest.U8_2.TheInquisitionQuest.Mission01, storageValue = 7 },
	{ storage = Storage.Quest.U8_2.TheInquisitionQuest.Mission02, storageValue = 3 },
	{ storage = Storage.Quest.U8_2.TheInquisitionQuest.Mission03, storageValue = 6 },
	{ storage = Storage.Quest.U8_2.TheInquisitionQuest.Mission04, storageValue = 3 },
	{ storage = Storage.Quest.U8_2.TheInquisitionQuest.Mission05, storageValue = 3 },
	{ storage = Storage.Quest.U8_2.TheInquisitionQuest.Mission06, storageValue = 3 },
	{ storage = Storage.Quest.U8_2.TheInquisitionQuest.Mission07, storageValue = 1 },
	{ storage = Storage.Quest.U8_2.TheInquisitionQuest.GrofGuard, storageValue = 1 },
	{ storage = Storage.Quest.U8_2.TheInquisitionQuest.KulagGuard, storageValue = 1 },
	{ storage = Storage.Quest.U8_2.TheInquisitionQuest.TimGuard, storageValue = 1 },
	{ storage = Storage.Quest.U8_2.TheInquisitionQuest.WalterGuard, storageValue = 1 },
	{ storage = Storage.Quest.U8_2.TheInquisitionQuest.StorkusVampiredust, storageValue = 1 },
	{ storage = Storage.Quest.U8_54.TheNewFrontier.Questline, storageValue = 29 },
	{ storage = Storage.Quest.U8_54.TheNewFrontier.Mission01, storageValue = 3 },
	{ storage = Storage.Quest.U8_54.TheNewFrontier.Mission02[1], storageValue = 4 },
	{ storage = Storage.Quest.U8_54.TheNewFrontier.Mission03, storageValue = 3 },
	{ storage = Storage.Quest.U8_54.TheNewFrontier.Mission04, storageValue = 2 },
	{ storage = Storage.Quest.U8_54.TheNewFrontier.Mission05[1], storageValue = 2 },
	{ storage = Storage.Quest.U8_54.TheNewFrontier.Mission06, storageValue = 5 },
	{ storage = Storage.Quest.U8_54.TheNewFrontier.Mission07[1], storageValue = 2 },
	{ storage = Storage.Quest.U8_54.TheNewFrontier.Mission08, storageValue = 2 },
	{ storage = Storage.Quest.U8_54.TheNewFrontier.Mission09[1], storageValue = 3 },
	{ storage = Storage.Quest.U8_54.TheNewFrontier.Mission10[1], storageValue = 2 },
	{ storage = Storage.Quest.U8_54.TheNewFrontier.Mission10.MagicCarpetDoor, storageValue = 1 },
	{ storage = Storage.Quest.U8_54.TheNewFrontier.TomeofKnowledge, storageValue = 12 },
	{ storage = Storage.Quest.U8_54.TheNewFrontier.Mission02.Beaver1, storageValue = 1 },
	{ storage = Storage.Quest.U8_54.TheNewFrontier.Mission02.Beaver2, storageValue = 1 },
	{ storage = Storage.Quest.U8_54.TheNewFrontier.Mission02.Beaver3, storageValue = 1 },
	{ storage = Storage.Quest.U8_54.TheNewFrontier.Mission05.KingTibianus, storageValue = 1 },
	{ storage = Storage.Quest.U8_54.TheNewFrontier.Mission05.Leeland, storageValue = 1 },
	{ storage = Storage.Quest.U8_54.TheNewFrontier.Mission05.Angus, storageValue = 1 },
	{ storage = Storage.Quest.U8_54.TheNewFrontier.Mission05.Wyrdin, storageValue = 1 },
	{ storage = Storage.Quest.U8_54.TheNewFrontier.Mission05.Telas, storageValue = 1 },
	{ storage = Storage.Quest.U8_54.TheNewFrontier.Mission05.Humgolf, storageValue = 1 },
	{ storage = Storage.Quest.U7_8.TheShatteredIsles.DefaultStart, storageValue = 3 },
	{ storage = Storage.Quest.U7_8.TheShatteredIsles.TheGovernorDaughter, storageValue = 3 },
	{ storage = Storage.Quest.U7_8.TheShatteredIsles.TheErrand, storageValue = 2 },
	{ storage = Storage.Quest.U7_8.TheShatteredIsles.AccessToMeriana, storageValue = 1 },
	{ storage = Storage.Quest.U7_8.TheShatteredIsles.APoemForTheMermaid, storageValue = 3 },
	{ storage = Storage.Quest.U7_8.TheShatteredIsles.ADjinnInLove, storageValue = 5 },
	{ storage = Storage.Quest.U7_8.TheShatteredIsles.AccessToLagunaIsland, storageValue = 1 },
	{ storage = Storage.Quest.U7_8.TheShatteredIsles.AccessToGoroma, storageValue = 1 },
	{ storage = Storage.Quest.U7_8.TheShatteredIsles.Shipwrecked, storageValue = 2 },
	{ storage = Storage.Quest.U7_8.TheShatteredIsles.DragahsSpellbook, storageValue = 1 },
	{ storage = Storage.Quest.U7_8.TheShatteredIsles.TheCounterspell, storageValue = 4 },
	{ storage = Storage.Quest.U8_2.TheThievesGuildQuest.Questline, storageValue = 1 },
	{ storage = Storage.Quest.U8_2.TheThievesGuildQuest.Mission01, storageValue = 2 },
	{ storage = Storage.Quest.U8_2.TheThievesGuildQuest.Mission02, storageValue = 3 },
	{ storage = Storage.Quest.U8_2.TheThievesGuildQuest.Mission03, storageValue = 3 },
	{ storage = Storage.Quest.U8_2.TheThievesGuildQuest.Mission04, storageValue = 8 },
	{ storage = Storage.Quest.U8_2.TheThievesGuildQuest.Mission05, storageValue = 2 },
	{ storage = Storage.Quest.U8_2.TheThievesGuildQuest.Mission06, storageValue = 4 },
	{ storage = Storage.Quest.U8_2.TheThievesGuildQuest.Mission07, storageValue = 2 },
	{ storage = Storage.Quest.U8_2.TheThievesGuildQuest.Mission08, storageValue = 1 },
	{ storage = Storage.Quest.U8_1.TheTravellingTrader.Mission01, storageValue = 1 },
	{ storage = Storage.Quest.U8_1.TheTravellingTrader.Mission01, storageValue = 2 },
	{ storage = Storage.Quest.U8_1.TheTravellingTrader.Mission02, storageValue = 5 },
	{ storage = Storage.Quest.U8_1.TheTravellingTrader.Mission03, storageValue = 3 },
	{ storage = Storage.Quest.U8_1.TheTravellingTrader.Mission04, storageValue = 3 },
	{ storage = Storage.Quest.U8_1.TheTravellingTrader.Mission05, storageValue = 3 },
	{ storage = Storage.Quest.U8_1.TheTravellingTrader.Mission06, storageValue = 2 },
	{ storage = Storage.Quest.U8_1.TheTravellingTrader.Mission07, storageValue = 1 },
	{ storage = Storage.Quest.U8_0.BarbarianArena.QuestLogGreenhorn, storageValue = 1 },
	{ storage = Storage.TibiaTales.DefaultStart, storageValue = 1 },
	{ storage = Storage.TibiaTales.ToAppeaseTheMightyQuest, storageValue = 1 },
	{ storage = 12450, storageValue = 6 },
	{ storage = 12330, storageValue = 1 },
	{ storage = 12332, storageValue = 13 },
	{ storage = 12333, storageValue = 3 },
	{ storage = Storage.Quest.U7_8.FriendsAndTraders.DefaultStart, storageValue = 1 },
	{ storage = Storage.Quest.U7_8.FriendsAndTraders.TheSweatyCyclops, storageValue = 2 },
	{ storage = Storage.Quest.U7_8.FriendsAndTraders.TheMermaidMarina, storageValue = 2 },
	{ storage = Storage.Quest.U7_8.FriendsAndTraders.TheBlessedStake, storageValue = 12 },
	{ storage = 100157, storageValue = 1 },
	{ storage = Storage.WrathoftheEmperor.Questline, storageValue = 29 },
	{ storage = Storage.WrathoftheEmperor.Mission01, storageValue = 3 },
	{ storage = Storage.WrathoftheEmperor.Mission02, storageValue = 3 },
	{ storage = Storage.WrathoftheEmperor.Mission03, storageValue = 3 },
	{ storage = Storage.WrathoftheEmperor.Mission04, storageValue = 3 },
	{ storage = Storage.WrathoftheEmperor.Mission05, storageValue = 3 },
	{ storage = Storage.WrathoftheEmperor.Mission06, storageValue = 4 },
	{ storage = Storage.WrathoftheEmperor.Mission07, storageValue = 6 },
	{ storage = Storage.WrathoftheEmperor.Mission08, storageValue = 2 },
	{ storage = Storage.WrathoftheEmperor.Mission09, storageValue = 2 },
	{ storage = Storage.WrathoftheEmperor.Mission10, storageValue = 1 },
	{ storage = Storage.Quest.U7_6.TheApeCity.Started, storageValue = 1 },
	{ storage = Storage.Quest.U7_6.TheApeCity.Questline, storageValue = 18 },
	{ storage = Storage.BanutaSecretTunnel.DeeperBanutaShortcut, storageValue = 1 },
	{ storage = Storage.Oramond.QuestLine, storageValue = 1 },
	{ storage = Storage.Oramond.MissionToTakeRoots, storageValue = 3000 },
	{ storage = Storage.DangerousDepths.Questline, storageValue = 1 },
	{ storage = Storage.DangerousDepths.Dwarves.Home, storageValue = 2 },
	{ storage = Storage.DangerousDepths.Dwarves.Subterranean, storageValue = 2 },
	{ storage = Storage.DangerousDepths.Gnomes.Measurements, storageValue = 2 },
	{ storage = Storage.DangerousDepths.Gnomes.Ordnance, storageValue = 3 },
	{ storage = Storage.DangerousDepths.Gnomes.Charting, storageValue = 2 },
	{ storage = Storage.DangerousDepths.Scouts.Growth, storageValue = 2 },
	{ storage = Storage.DangerousDepths.Scouts.Diremaw, storageValue = 2 },
	{ storage = Storage.Quest.U11_40.ThreatenedDreams.QuestLine, storageValue = 1 },
	{ storage = Storage.Quest.U11_40.ThreatenedDreams.Mission01[1], storageValue = 16 },
	{ storage = Storage.Quest.U11_40.ThreatenedDreams.Mission02.KroazurAccess, storageValue = 1 },
	{ storage = Storage.AdventurersGuild.QuestLine, storageValue = 1 },
	{ storage = Storage.AdventurersGuild.GreatDragonHunt.WarriorSkeleton, storageValue = 1 },
	{ storage = Storage.AdventurersGuild.GreatDragonHunt.WarriorSkeleton, storageValue = 2 },
	{ storage = Storage.AdventurersGuild.TheLostBrother, storageValue = 3 },
	{ storage = Storage.Quest.U10_55.Dawnport.Questline, storageValue = 1 },
	{ storage = Storage.Quest.U10_55.Dawnport.GoMain, storageValue = 1 },
	{ storage = Storage.ForgottenKnowledge.AccessDeath, storageValue = 1 },
	{ storage = Storage.ForgottenKnowledge.AccessViolet, storageValue = 1 },
	{ storage = Storage.ForgottenKnowledge.AccessEarth, storageValue = 1 },
	{ storage = Storage.ForgottenKnowledge.AccessFire, storageValue = 1 },
	{ storage = Storage.ForgottenKnowledge.AccessIce, storageValue = 1 },
	{ storage = Storage.ForgottenKnowledge.AccessGolden, storageValue = 1 },
	{ storage = Storage.Quest.U10_80.Grimvale.AncientFeudDoors, storageValue = 1 },
	{ storage = Storage.Quest.U10_80.Grimvale.AncientFeudShortcut, storageValue = 1 },
	{ storage = Storage.Kilmaresh.AccessDoor, storageValue = 1 },
	{ storage = Storage.Kilmaresh.CatacombDoors, storageValue = 1 },
	{ storage = Storage.Quest.U12_00.TheDreamCourts.AccessDoors, storageValue = 1 },
	{ storage = Storage.Quest.U12_00.TheDreamCourts.HauntedHouseAccess, storageValue = 1 },
	{ storage = Storage.Quest.U12_00.TheDreamCourts.BuriedCathedralAccess, storageValue = 1 },
	{ storage = Storage.Quest.U12_00.TheDreamCourts.DreamScarAccess, storageValue = 1 },
	{ storage = Storage.Quest.U12_40.TheOrderOfTheLion.AccessEastSide, storageValue = 1 },
	{ storage = Storage.Quest.U12_40.TheOrderOfTheLion.AccessSouthernSide, storageValue = 1 },
	{ storage = Storage.Quest.U12_60.APiratesTail.TentuglyDoor, storageValue = 1 },
	{ storage = Storage.Quest.U12_60.APiratesTail.RascacoonShortcut, storageValue = 1 },
	{ storage = Storage.Quest.U12_70.AdventuresOfGalthen.AccessDoor, storageValue = 1 },

	{ storage = Storage.CultsOfTibia.Barkless.AccessDoor, storageValue = 1 },
	{ storage = Storage.CultsOfTibia.Barkless.TrialAccessDoor, storageValue = 1 },
	{ storage = Storage.CultsOfTibia.Barkless.TarAccessDoor, storageValue = 1 },
	{ storage = Storage.CultsOfTibia.Barkless.BossAccessDoor, storageValue = 1 },
	{ storage = Storage.CultsOfTibia.Life.AccessDoor, storageValue = 1 },
	{ storage = Storage.CultsOfTibia.Misguided.AccessDoor, storageValue = 1 },
	{ storage = Storage.CultsOfTibia.FinalBoss.AccessDoor, storageValue = 1 },

	{ storage = Storage.FerumbrasAscension.FirstDoor, storageValue = 1 },
	{ storage = Storage.FerumbrasAscension.MonsterDoor, storageValue = 1 },
	{ storage = Storage.FerumbrasAscension.TarbazDoor, storageValue = 1 },
	{ storage = Storage.FerumbrasAscension.HabitatsAccess, storageValue = 1 },
	{ storage = Storage.FerumbrasAscension.TheLordOfTheLiceAccess, storageValue = 1 },
	{ storage = Storage.FerumbrasAscension.Statue, storageValue = 1 },

	{ storage = Storage.Quest.U12_00.TheDreamCourts.AndrewDoor, storageValue = 1 },

	{ storage = Storage.WrathoftheEmperor.TeleportAccess.AwarnessEmperor, storageValue = 1 },
	{ storage = Storage.WrathoftheEmperor.TeleportAccess.BossRoom, storageValue = 1 },
	{ storage = Storage.WrathoftheEmperor.TeleportAccess.InnerSanctum, storageValue = 1 },
	{ storage = Storage.WrathoftheEmperor.TeleportAccess.Rebel, storageValue = 1 },
	{ storage = Storage.WrathoftheEmperor.TeleportAccess.SleepingDragon, storageValue = 2 },
	{ storage = Storage.WrathoftheEmperor.TeleportAccess.Wote10, storageValue = 1 },
	{ storage = Storage.WrathoftheEmperor.TeleportAccess.Zizzle, storageValue = 1 },
	{ storage = Storage.WrathoftheEmperor.TeleportAccess.Zlak, storageValue = 1 },

	{ storage = Storage.TheSecretLibrary.FalconBastionAccess, storageValue = 1 },
	{ storage = Storage.TheSecretLibrary.LowerBastionAccess, storageValue = 1 },
	{ storage = Storage.TheSecretLibrary.UndergroundBastionAccess, storageValue = 1 },
	{ storage = Storage.TheSecretLibrary.ShortcutToBastion, storageValue = 1 },
	{ storage = Storage.TheSecretLibrary.OberonAccess, storageValue = 1 },
	{ storage = Storage.TheSecretLibrary.MotaDoor, storageValue = 1 },
	{ storage = Storage.TheSecretLibrary.BasinDoor, storageValue = 1 },
	{ storage = Storage.TheSecretLibrary.SkullDoor, storageValue = 1 },
	{ storage = Storage.TheSecretLibrary.Mota, storageValue = 1 },
	{ storage = Storage.TheSecretLibrary.MiniBosses.PreceptorLazare, storageValue = 1 },
	{ storage = Storage.TheSecretLibrary.MiniBosses.GrandCanonDominus, storageValue = 1 },
	{ storage = Storage.TheSecretLibrary.MiniBosses.GrandChaplainGaunder, storageValue = 1 },
	{ storage = Storage.TheSecretLibrary.MiniBosses.GrandCommanderSoeren, storageValue = 1 },
	{ storage = Storage.TheSecretLibrary.MiniBosses.DazedLeafGolem, storageValue = 1 },

	{ storage = Storage.Quest.U7_4.DjinnWar.EfreetFaction.DoorToLamp, storageValue = 1 },
	{ storage = Storage.Quest.U7_4.DjinnWar.EfreetFaction.DoorToMaridTerritory, storageValue = 1 },
	{ storage = Storage.Quest.U7_4.DjinnWar.MaridFaction.DoorToLamp, storageValue = 1 },
	{ storage = Storage.Quest.U7_4.DjinnWar.MaridFaction.DoorToEfreetTerritory, storageValue = 1 },

	{ storage = Storage.Quest.U12_20.GraveDanger.QuestLine, storageValue = 14 },
	{ storage = Storage.Quest.U12_20.GraveDanger.Bosses.KingZelosDoor, storageValue = 1 },

	{ storage = Storage.Quest.U13_10.CradleOfMonsters.Access.Ingol, storageValue = 1 },
	{ storage = Storage.Quest.U13_10.CradleOfMonsters.Access.LowerIngol, storageValue = 1 },
	{ storage = Storage.Quest.U13_10.CradleOfMonsters.Access.Monster, storageValue = 1 },
	{ storage = Storage.Quest.U13_10.CradleOfMonsters.Access.MutatedAbomination, storageValue = 1 },
	{ storage = Storage.Quest.U8_54.TheNewFrontier.SnakeHeadTeleport, storageValue = 1 },
	{ storage = Storage.LiquidBlackQuest.Visitor, storageValue = 5 },
	{ storage = Storage.Quest.U8_4.BloodBrothers.VengothAccess, storageValue = 1 },

	-- Assassin Outfit quests
	{ storage = Storage.KillingInTheNameOf.BudrikMinos, storageValue = 0 },
	{ storage = Storage.TibiaTales.ToOutfoxAFoxQuest.Questline, storageValue = 2 },

	-- Hunter Outfit quests
	{ storage = Storage.Quest.U7_8.HunterOutfits.HunterMusicSheet01, storageValue = 1 },
	{ storage = Storage.Quest.U7_8.HunterOutfits.HunterMusicSheet02, storageValue = 1 },
	{ storage = Storage.Quest.U7_8.HunterOutfits.HunterMusicSheet03, storageValue = 1 },
	{ storage = Storage.Quest.U7_8.HunterOutfits.HunterMusicSheet04, storageValue = 1 },

	-- Norseman
	{ storage = Storage.Quest.U8_0.TheIceIslands.NorsemanOutfit, storageValue = 1 },
	{ storage = Storage.OutfitQuest.DefaultStart, storageValue = 1 },

	{ storage = Storage.HeroRathleton.AccessDoor, storageValue = 1 },
	{ storage = Storage.HeroRathleton.AccessTeleport1, storageValue = 1 },
	{ storage = Storage.HeroRathleton.AccessTeleport2, storageValue = 1 },
	{ storage = Storage.HeroRathleton.AccessTeleport3, storageValue = 1 },

	-- Sea Serpent Quest
	{ storage = Storage.Quest.U8_2.TheHuntForTheSeaSerpent.FishForASerpent, storageValue = 5 },
	{ storage = Storage.Quest.U8_2.TheHuntForTheSeaSerpent.QuestLine, storageValue = 2 },

	--The White Raven Monastery
	{ storage = Storage.WhiteRavenMonastery.QuestLog, storageValue = 1 },
	{ storage = Storage.WhiteRavenMonastery.Passage, storageValue = 1 },
	{ storage = Storage.WhiteRavenMonastery.Diary, storageValue = 2 },
	{ storage = Storage.WhiteRavenMonastery.Door, storageValue = 1 },
}

-- from Position: (33201, 31762, 1)
-- to Position: (33356, 31309, 4)
local function playerFreeQuestStart(playerId, index)
	local player = Player(playerId)
	if not player then
		return
	end

	for i = 1, 5 do
		index = index + 1
		if not questTable[index] then
			player:sendTextMessage(MESSAGE_LOOK, "Adding free quests completed.")
			player:setStorageValue(Storage.FreeQuests, stage)
			return
		end

		if player:getStorageValue(questTable[index].storage) ~= questTable[index].storageValue then
			player:setStorageValue(questTable[index].storage, questTable[index].storageValue)
		end
	end

	addEvent(playerFreeQuestStart, 500, playerId, index)
end

local freeQuests = CreatureEvent("FreeQuests")

function freeQuests.onLogin(player)
	if not configManager.getBoolean(configKeys.TOGGLE_FREE_QUEST) or player:getStorageValue(Storage.FreeQuests) == stage then
		return true
	end

	player:sendTextMessage(MESSAGE_LOOK, "Adding free acccess quests to your character.")
	addEvent(playerFreeQuestStart, 500, player:getId(), 0)
	player:addOutfit(251, 0)
	player:addOutfit(252, 0)

	return true
end

freeQuests:register()
