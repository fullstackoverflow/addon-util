import { Expect, TestFixture, Test, Timeout, SetupFixture, Focus, Ignore } from 'alsatian';
import { Util } from '../lib/lib';

@TestFixture('Util test')
export class UtilTest {

	instance: Util

	@SetupFixture
	init() {
		this.instance = new Util()
	}

	@Test('Test AsyncWorker')
	@Timeout(50000)
	public async t1() {
		const { result, tag } = await this.instance.AsyncWorker(1, 2);
		Expect(result).toEqual(3);
		Expect(tag).toEqual(true);
	}
}
