// https://www.techiedelight.com/find-distinct-combinations-given-length-repetition-allowed/ backup
/*std::vector<std::vector<int>> FindAllDistinctCombos(std::vector<int> nums, int k)
{
	std::vector<std::vector<int>> AllCombos;
	std::vector<int> NewCombo(k);
	std::vector<int> elementshit(k);

	if (nums.size() < k)
	{
		return std::vector<std::vector<int>>();
	}

	std::sort(nums.begin(), nums.end());

	for (int x = 0; x < nums.size(); x++)
	{
		if (x + 1 < nums.size() && nums[x + 1] == nums[x])
		{
			continue;
		}

		NewCombo = std::vector<int>(k, nums[x]);
		elementshit = std::vector<int>(k, x);
		AllCombos.push_back(NewCombo);
		do
		{
			NewCombo[k - 1] = CycleElements(nums, elementshit[k - 1], k);
			if (NewCombo[k - 1] != -1)
			{
				AllCombos.push_back(NewCombo);
			}
			else
			{
				int PrevE = k - 2;
				elementshit[k - 1] = elementshit[PrevE];
				while (elementshit[PrevE] >= x && PrevE > 0)
				{
					NewCombo[PrevE] = CycleElements(nums, elementshit[PrevE], k);
					if (NewCombo[PrevE] != -1)
					{
						for (int r = PrevE + 1; r < elementshit.size(); r++)
						{
							elementshit[r] = elementshit[PrevE];
							NewCombo[r] = NewCombo[PrevE];
						}
						elementshit[k - 1]--;
						break;
					}
					PrevE--;
				}

			}
		} while (NewCombo[k - 1] != -1 && elementshit[0] < k);
	}

	return AllCombos;
}*/