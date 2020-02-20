using uint32 = uint32_t;

struct wavelet_matrix
{
	using bit_array = vector<int>;

	wavelet_matrix() = default;
	wavelet_matrix(const vector<uint32> &data, uint32 m_level = 0)
	{
		n = data.size();
		max_value = (n == 0 ? 0UL : *max_element(data.begin(), data.end()));
		if (m_level == 0)
			do { ++m_level; } while ((1UL << m_level) <= max_value);
		max_level = m_level;
		bit_arrays.assign(max_level, bit_array(n));
		zero_cnt.assign(max_level, 0UL);
		vector<uint32> level = data, next_level = level;
		for (uint32 lvl = 0; lvl < max_level; ++lvl)
		{
			uint32 mask = 1UL << (max_level - lvl - 1);
			uint32 &zeros = zero_cnt[lvl] = 0;
			for (uint32 i = 0; i < n; ++i)
				zeros += (level[i] & mask) == 0;
			bit_array &ba = bit_arrays[lvl];
			uint32 zero_pos = 0, one_pos = zeros;
			for (uint32 i = 0; i < n; ++i)
				if (level[i] & mask)
					ba[i] = 1, next_level[one_pos++] = level[i];
				else next_level[zero_pos++] = level[i];
			for (int i = 1; i < n; ++i)
				ba[i] += ba[i - 1];
			level.swap(next_level);
		}
	}
	// Compute the frequency of characters c' < c, c'= c, and c' > c, in the subarray [begin_pos...end_pos)
	tuple<uint32, uint32, uint32> rank_all(uint32 c, uint32 begin_pos, uint32 end_pos) const
	{
		if (c > max_value) return make_tuple(end_pos - begin_pos, 0UL, 0UL);
		uint32 more_and_less[2] = {0};
		for (uint32 lvl = 0; lvl < max_level; ++lvl)
		{
			const bit_array &ba = bit_arrays[lvl];
			const bool one = (c >> (max_level - lvl - 1)) & 1;
			more_and_less[one] += end_pos - begin_pos;
			begin_pos = rank(ba, begin_pos, one);
			end_pos = rank(ba, end_pos, one);
			if (one) begin_pos += zero_cnt[lvl], end_pos += zero_cnt[lvl];
			more_and_less[one] -= end_pos - begin_pos;
		}
		return make_tuple(more_and_less[1], end_pos - begin_pos, more_and_less[0]);
	}
private:
	uint32 n;
	uint32 max_level;
	uint32 max_value;
	vector<bit_array> bit_arrays;
	vector<uint32> zero_cnt;

	static inline uint32 rank(const bit_array &ba, uint32 pos, bool one)
	{
		uint32 sum = (pos >= 1 ? ba[pos - 1] : 0);
		return one ? sum : pos - sum;
	}
};
